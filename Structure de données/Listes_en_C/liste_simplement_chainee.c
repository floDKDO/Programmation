#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct listeSimple
{
	int v; //valeur d'un noeud
	struct listeSimple *s; //element suivant
} ListeSimple, *Liste;



Liste liste_vide()
{
	return NULL;
}


Liste ajout_tete(Liste l, int v) //on veut ajouter le noeud v a la liste l
{
	Liste nouv = malloc(sizeof(ListeSimple)); //on alloue le noeud
	if(nouv == NULL) //si le malloc echoue
	{
		printf("Erreur lors du malloc");
		exit(EXIT_FAILURE);
	}

	nouv->v = v; //on donne la valeur v à ce noeud
	nouv->s = l; //pointer sur l'anciennce tete de la liste l avec ses autres valeurs
	return nouv; //retourne la liste avec la nouvelle tete et les autres valeurs de la liste l
}


Liste ajout_queue(Liste l, int v)
{
	Liste nouv = malloc(sizeof(ListeSimple));
	Liste nouv_2 = malloc(sizeof(ListeSimple)); 
	nouv = l;
	nouv_2->v = v;
	nouv_2->s = NULL;

	while(nouv->s != NULL)
	{
		nouv = nouv->s;
	}
	nouv->s = nouv_2;
	return nouv_2;
}

bool est_vide(Liste l)
{
	return l == NULL; //on regarde si la liste l est vide si elle est vide
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


Liste suppression_tete(Liste l)
{
	if(est_vide(l))
	{
		return l; //si la liste est vide, elle n'a pas de tete donc on la retourne car rien a faire
	}

	Liste nouv = l->s; //cette liste represente la liste l sans son premier noued donc sans sa tete
	free(l);
	return nouv; //on retourne cette liste sans la tete de l
}


Liste suppression_queue(Liste l)
{
	if(l == NULL)
	{
		return l;
	}
	else
	{
		if(l->s == NULL)
		{
			free(l);
			l = NULL;
		}
		else
		{
			Liste nouv = l;
			while(nouv->s->s != NULL)
			{
				nouv = nouv->s;
			}
			free(nouv->s);
			nouv->s = NULL;
		}
	}
	return l;
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


Liste insert(Liste l, int i, int v)
{
	if(l == NULL || i == 0)//une fois qu'on a atteint l'indice en parametre
	{
		Liste nouv = malloc(sizeof(ListeSimple)); //on cree une liste
		nouv->s = l; //ce noeud va pointer sur le noeud suivant de la liste l
		nouv->v = v; //on donne la valeur v a ce noeud
		l = nouv; //on remplace la liste avec l'element insere
	}
	else
	{
		l->s = insert(l->s, i-1, v); //on parcourt la liste recursivement en decrementant l'indice et en pointant sur le noeud suivant de la liste l
	}
	return l; //la liste avec l'element insere
}


void printListeSimple(Liste l)
{
	while(l != NULL)
	{
		printf("%d ", l->v);
		l = l->s;
	}
}




