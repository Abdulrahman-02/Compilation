// Analyseur lexicale

#include <stdio.h>
#include <stdlib.h>

enum Token{FIN,PV,AFFECT,COND,ACG,ACD,ID,NUM,OP};   // Codification des Tokens

char programme[512];    // Programme source

int position,debut;   //Variable position

int table [6] [13] = {{7,8,14,9,1,12,13,13,4,5,5,-1,0,-1},
                     {-1,-1,-1,-1,-1,-1,-1,2,-1,-1,-1,-1,-1,6},
                     {-1,-1,-1,-1,-1,-1,-1,3,-1,-1,-1,-1,-1,2},
                     {-1,-1,-1,-1,-1,0,-1,3,-1,-1,-1,-1,-1,2},
                     {-1,-1,-1,-1,-1,-1,-1,-1,-1,4,4,4,-1,10},
                     {-1,-1,-1,-1,-1,-1,-1,-1,-1,5,5,-1,-1,11}
                     };    // Table de transition

/* La fonction car_suivant() retourne le code du prochain caractère du 
   programme source et incrémente la variable position */
int car_suivant(){
    char c;    // caractère courant
    c = programme[position];    // lecture de caractère    
    position++;     //incrémentation de la variable position

    if(c =='\0') return 0;
    if(c ==';') return 1 ;
    if(c =='=') return 2;
    if(c =='?') return 3;
    if(c =='{') return 4;
    if(c =='}') return 5;
    if(c =='+' || c == "-") return 6;
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
  case 10: reculer(); return ID; break;
  case 11: reculer(); return NUM; break;
  case 12: return ACD; break;
  case 13: return OP; break;
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
			case PV:printf("<PV>\n");
			case COND:printf("<COND>\n");
			case ID:printf("<ID>\n");
			case NUM:printf("<NUM>\n");
			case ACD:printf("<ACD>\n");
			case OP:printf("<OP>\n");
			case AFFECT:printf("<AFFECT>\n");
	}
}
printf("<FIN>\n");
}