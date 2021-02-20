#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>

typedef struct listeDouble
{
	int v; //valeur d'un noeud
	struct listeDouble *s; //element suivant
	struct listeDouble *p; //element precedent
} ListeDouble, *Liste;


Liste liste_vide()
{
	return NULL;
}


Liste ajout_tete(Liste l, int v)
{
	Liste nouv = malloc(sizeof(ListeDouble));

	if(nouv == NULL)
	{
		printf("Erreur lors du malloc");
		exit(EXIT_FAILURE);
	}
	nouv->v = v; //on donne la valeur v au noeud
	nouv->s = l; //l'element suivant pointe sera la liste l
	nouv->p = NULL; //l'element precedent du nouveau noueud pointe sera NULL

	if(l != NULL)
	{
		l->p = nouv; //l'element precedent de la liste l pointe sur la nouvelle tete
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
}


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


Liste ajout_queue(Liste l, int v)
{
	if(l->s == NULL) //si on a atteint le dernier noeud de la liste
	{
		Liste nouv = malloc(sizeof(ListeDouble)); //ce noeud representera la nouvelle queue
		nouv->s = NULL; //l'element suivant point sera NULL
		nouv->v = v; //on donne la valeur v au noeud
		nouv->p = l; //l'element precedent pointe sera la liste l (pointera sur la queue de l qui sera remplacee)
		l->s = nouv; //l'element suivant pointe (la queue de l qui sera remplacee) sera la nouvelle queue nouv
		return l; //on retourne la liste l avec sa nouvelle queue
	}
	ajout_queue(l->s, v); //on parcourt recursivement la liste l en allant a l'element suivant 
}


Liste suppression_tete(Liste l)
{
	if(est_vide(l))
	{
		return l;
	}
	Liste nouv = l->s; //on creer une nouvelle liste qui contient la liste l sans sa tete
	free(l); //on libere la liste l
	nouv->p = NULL; //l'element precedent de nouv sera NULL
	return nouv;
}



int acces(Liste l, int i) //retourne le ieme element de la liste
{
	if(i == 0)
	{
		return l;
	}
	else
	{
		return acces(l->s, i-1); //on passe au noeud suivant en decrementant l'indice de recherche
	}
}


Liste suppression_queue(Liste l)
{
	Liste nouv = l;
	Liste nouv_2 = malloc(sizeof(ListeDouble));
	while(nouv->s != NULL)
	{
		nouv = nouv->s;
	}
	nouv_2 = nouv->p;
	nouv_2->s = NULL;
	free(nouv);
	return l;
}


void printListeDouble(Liste l)
{
	Liste nouv = l;
	while(nouv != NULL)
	{
		printf("%d ", nouv->v);
		nouv = nouv->s;
	}
	printf("\n");
}

