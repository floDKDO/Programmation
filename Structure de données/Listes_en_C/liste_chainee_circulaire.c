#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct listeCirc
{
	int v;
	struct listeCirc *s;
}ListeCirc, *Liste;


Liste liste_vide()
{
	return NULL;
}


Liste ajout_tete(Liste l, int v)
{
	Liste nouv = (Liste) malloc(sizeof(ListeCirc)); //initialisation du noeud qui sera la nouvelle tete
	nouv->v = v; //on donne la valeur v au noeud

	if(l == NULL)
	{
		nouv->s = nouv; //si la liste ne fait qu'un element, comme elle est circulaire
						//le noeud va pointer sur lui meme
		return nouv;
	}
	else
	{
		nouv->s = l->s; //on pointe sur l'ancienne tete de la liste l
		l->s = nouv; //on fait pointer le suivant du dernier noeud sur la nouvelle tete
		return l;
	}
}


bool est_vide(Liste l)
{
	return l == NULL;//on regarde si la liste l est vide si elle est vide
					  //on retourne true sinon on retourne false
}


int tete(Liste l)
{
	return l->v; //on retourne la valeur du premier noeud de la liste l donc la tete


int longueur(Liste l)
{
	if(est_vide(l))
	{
		return 0; //si la liste est vide, on retourne une longueur de 0
	}
	else
	{
		return 1 + longueur(l->s); //sinon on retourne 1 + la longueur du reste de la liste 
								   //donc sans le premier noeud
	}
}


Liste suppression_tete(Liste l)
{
	if(est_vide(l))
	{
		return l;
	}

	if(l == l->s) //si la liste pointe sur elle-meme (si la liste n'a qu'un noeud)
	{
		return NULL; //on retourne la liste vide
	}
	else
	{
		l->s = l->s->s; //le debut de la liste sera le deuxieme noeud
		return l;
	}
	
}


Liste ajout_queue(Liste l, int v)
{
	Liste nouv = (Liste) malloc(sizeof(ListeCirc));
	nouv->v = v;
	nouv->s = NULL;
	nouv->s = l->s;
	l->s = nouv;
	l = nouv;
	return l;
}


Liste suppression_queue(Liste l)
{
	if(l == NULL)
	{
		return l;
	}

	Liste nouv = l->s;
	if(l->s == l)
	{
		free(l);
		l = NULL;
		return l;
	}
	while(nouv->s != l)
	{
		nouv = nouv->s;
	}
	nouv->s = l->s;
	free(l);
	l = nouv;
	return l;
}


void printListeCirculaire(Liste l)
{
   Liste nouv = l->s;
   do
   {
      printf("%d ", nouv->v);
      nouv = nouv->s;
   }while(nouv != l->s);
       
}

