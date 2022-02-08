// Analyseur lexicale

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Token{FIN,PV,AFFECT,COND,ACG,ACD,ID,NUM,OP};   // Codification des Tokens
enum CODEOPERATION{PLUS,MOINS,MODULO};


char programme[512];    // Programme source

int position,debut;   //Variable position

int table [6] [13] = {{7,8,14,9,1,12,13,13,4,5,5,-1,0,-1},
                     {6,6,6,6,6,6,6,2,6,6,6,6,6,6},
                     {2,2,2,2,2,2,2,3,2,2,2,2,2,2},
                     {2,2,2,2,2,0,2,3,2,2,2,2,2,2},
                     {10,10,10,10,10,10,10,10,10,4,4,4,10,10},
                     {11,11,11,11,11,11,11,11,11,5,5,11,11,11}
                     };    // Table de transition

/* cette variable contiendra la valeur
d'attribut du dernier token reconu */
union {
    char * nom;
    int valeur;
    enum CODEOPERATION cop;
} attribut;

/* La fonction get_lexeme() permet de recupérer le dernier lexème reconnu 
   Elle utilise les fonctions malloc() et strncpy() offertes, 
   respectivement, dans <stdlib.h> et <string.h> */
char* get_lexeme(){
    int longueur=position-debut;                 /* longueur du lexème. */

    char* lexeme=(char*) malloc(longueur+1);     /* allocation de l'espace mémoire. */
    strncpy(lexeme,programme+debut,longueur);    /* le lexème commence a l'adresse
                                                    programme+debut*/                                                
    lexeme[longueur]='\0';                       /* ajout de la marque de fin de cha�ne. */
    return lexeme;
}

/* La fonction car_suivant() retourne le code du prochain caractère du
   programme source et incrémente la variable position */
int car_suivant(){
    char c;    // caractère courant
    c = programme[position];    // lecture de caractère
    position++;     //incrémentation de la variable position

    if(c =='\0') return 0;
    if(c ==';') return 1;
    if(c =='=') return 2;
    if(c =='?') return 3;
    if(c =='{') return 4;
    if(c =='}') return 5;
    if(c =='+' || c == '-') return 6;
    if(c =='%') return 7;
    if(c == '$') return 8;
    if(c>='0' && c<='9') return 9;
    if(c>='A' && c<='F') return 10;
    if(c>='G' && c<='Z') return 11;
    if(c =='\t') return 12;
    return 13;

}

/* La fonction reculer() permet de reculer d'une position sur le programme
   source */
void reculer(){
    position --;
}

/* La fonction erreur_lexicale() est notre procédure de gestion d'erreurs
   lexicales: elle affiche message en cas d'erreur */
void erreur_lexicale(){
printf(" \n position %d: Erreur Lexicale,  CAR :\"%c\" Illegal ! \n ", position, programme[position-1]);
exit(-1);
}

/* token_suivant() est la fonction princiaple de l'analyseur lexical */
enum Token token_suivant(){
  int etat = 0;
  int cc;

    while(etat!=-1 && etat<=5){
        if (etat==0) debut = position;
          	cc=car_suivant();
  	        etat=table[etat][cc];
    }
  switch (etat)
  {
  case 6: return ACG; break;
  case 7: return FIN; break;
  case 8: return PV; break;
  case 9: return COND; break;
  case 10: reculer(); attribut.nom=get_lexeme(); return ID; break;
  case 11: reculer(); attribut.valeur=atoi(get_lexeme()); return NUM; break;
  case 12: return ACD; break;
  case 13: if(get_lexeme()[0]=='+') attribut.cop=PLUS;
           else if(get_lexeme()[0]=='%') attribut.cop=MODULO;   /* déterminer et positionner le code d'opération */
           else attribut.cop=MOINS; return OP; break;
  case 14: return AFFECT; break;
  default: erreur_lexicale(); break;
  }
}

// Programme Principale
void main(){
    enum Token tc;  /* token suivant */

    printf("Taper un programme:\n");
    printf("------------------\n");
    scanf("%s", programme);

    position=0;

    printf("\n\nSéquence des couples <token, attribut>\n");
    printf("--------------------------------------\n");

	while(tc= token_suivant()){
		switch(tc){
			case ACG:printf("<ACG>\n"); break;
			case FIN:printf("<FIN>\n");break;
			case PV:printf("<PV>\n");break;
			case COND:printf("<COND>\n");break;
			case ID:printf("<ID, \"%s\">\n",attribut.nom);break;
			case NUM:printf("<NUM, %d>\n",attribut.valeur);break;
			case ACD:printf("<ACD>\n");break;
			case OP:printf("<OP, ");
              if (attribut.cop==PLUS) printf("PLUS>\n");
              else if (attribut.cop==MODULO) printf("MODULO>\n");
              else printf("MOINS>\n");break;
			case AFFECT:printf("<AFFECT>\n");break;
	}
}
printf("<FIN>\n");
}
