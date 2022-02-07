
/*  Implementation de l'analyseur lexical en utilisant la table deq transitions, pour le mini langage
                                 d�crit par la grammaire :
                                        
         L-->(L)|num
         
*/



#include<stdio.h>
#include<stdlib.h>

enum Token{FIN,PARG,PARD,NUM};      /* codification des tokens */

char programme[256];               /* contiendra la cha�ne d'entr�e; i.e., le programme source. */

int position;

int table [2] [5] = { {2, 3, 4, 1, -1}, {5, 5, 5, 1, 5} } ; /* Tables des transitions associ�e au DFA

/* La fonction car_suivant() retourne le code du prochain caract�re du 
   programme source et incr�mente la variable position.  C'est cette fonction
   qui assure la codification des caract�res.
*/

int car_suivant(){
    char c;                         /* caract�re courant */
    
    c=programme[position];          /* lecture du caract�re et incr�mentation de la variable position. */
    position++;
    
    if(c=='\0') return 0;
    if(c=='(') return 1;
    if(c==')') return 2;
    if(c>='0'&&c<='9') return 3;
    return 4;                      /* autre */
}


/* La fonction reculer() permet de reculer d'une position sur le programme
   source.
*/
void reculer(){
    position --;
}

/* La fonction erreur_lexicale() est notre proc�dure de gestion d'erreurs
   lexicales: elle affiche message en cas d'erreur
*/
void erreur_lexicale(){

printf("\nposition %d: Erreur Lexicale,  CAR :\"%c\" Illegal ! \n",position,programme[position-1]);
exit(-1);
 
}



/* token_suivant() est la fonction princiaple de l'analyseur lexical; c'est
   elle qui assure la simulation du DFA. A chaque appel, elle retourne le 
   prochain token.
*/

enum Token token_suivant(){
  int etat ;
  int cc;
  etat=0;
  while(etat!=-1 && etat<=1){
  	
  	cc=car_suivant();
  	etat=table[etat][cc];
  }
  
     switch(etat){
               
       case 2: return FIN;
       
       case 3: return PARG;
       
       case 4: return PARD;
       
       case 5: reculer();
               return NUM;
        default: erreur_lexicale();

      }
   }


/* En pratique, la fonction principale main() n'est pas n�cessaire; sa 
   pr�sence ne se justifie que par l'absence d'un analyseur syntaxique 
   qui ferait appel � la fonction token_suivant(). 
*/

void main(){
    enum Token tc;         /* token suivant */
  
    printf("Taper un programme:\n");
    printf("------------------\n\n");
    scanf("%s", programme);
  
    position=0;
  
    printf("\n\nS�quence des couples <token, attribut>\n");
    printf("--------------------------------------\n");
    
	while(tc= token_suivant()){
		switch(tc){
			case PARG:printf("<PARG>\n"); break;
			case PARD:printf("<PARD>\n");break;
			case NUM:printf("<NUM>\n");
	}
}
printf("<FIN>\n");
}