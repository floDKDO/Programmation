#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int S;
typedef unsigned Nat;

#define OMEGA 0


// Représentation d'un graphe par liste d'adjacence
///////////////////////////////////////////////////

typedef struct strarc {
	S v;
	struct strarc *suc;
} Strarc, *ListeSom;

typedef struct {
	S v;
	ListeSom ls;
} Couple; 

typedef struct strsom {
	Couple c;
	struct strsom *suiv;
} Strsom, *Graphe;


// Operations internes sur des listes de sommets ListeSom
////////////////////////////////////////////////////

ListeSom _nouvls() 
{ 
	return NULL;  
}


ListeSom _adjtetels(ListeSom l, S x)
{
	ListeSom n = (ListeSom)malloc(sizeof(Strarc));
	if (n == NULL) 
	{ 
		printf("fatal error: no memory allocation possible.\n"); 
		abort(); //arrête le programme
	}
	n->suc = l;
	n->v = x;
	return n;
}


ListeSom _rechls(ListeSom l, S x)
{
	if (l == NULL)
	{
		return NULL;
	}
	if (l->v == x)
	{ 
		return l;
	}
	return _rechls(l->suc, x);
}


int _rangls(ListeSom l, S x)
{
	if (l == NULL)
	{
		return -1;
	}
	if (x==l->v)
	{
		return 0;
	} 
	int r = _rangls(l->suc, x);

	if (r == -1)
	{ 
		return -1;
	} 
	else 
	{
		return r + 1;
	}
}


ListeSom _supkiemels(ListeSom l, Nat k)
{
	if (l == NULL) // this should never happen
	{
		return NULL;
	} 
	if (k == 0)
	{
		ListeSom n = l->suc;
		free(l);
		return n;
	}
	l->suc = _supkiemels(l->suc, k - 1);
	return l;
}


S _kiemels(ListeSom l, Nat k)
{
	if (l == NULL) // this should never happen
	{ 
		return OMEGA; 
	}
	if (k == 0)
	{
		return l->v;
	} 
	return _kiemels(l->suc, k - 1);
}


bool _videls(ListeSom l) 
{ 
	return l == NULL; 
}


Nat _longueurls(ListeSom l) 
{ 
	if (l == NULL)
	{
		return 0;
	}  
	else 
	{
		return 1 + _longueurls(l->suc); 
	}
}


void _destroyls(ListeSom l)
{
	while (l != NULL)
	{
		ListeSom n = l->suc;
		free(l);
		l = n;
	}
}


// Operations internes sur des listes de couples
////////////////////////////////////////////

Strsom *_nouvlsom() 
{ 
	return NULL; 
}


Strsom *_adjtetelsom(Strsom * l, S x)
{
	Strsom * n = (Strsom *)malloc(sizeof(Strsom));
	if (n == NULL) 
	{ 	printf("fatal error: no memory allocation possible.\n"); 
		abort(); 
	}
	n->suiv = l;
	n->c.v = x;
	n->c.ls = _nouvls();
	return n;
}


Strsom * _rechlsom(Strsom * l, S x)
{
	if (l == NULL)
	{
		return NULL;
	} 
	if (x==l->c.v)
	{
		return l;
	} 
	return _rechlsom(l->suiv, x);
}


int _ranglsom(Strsom * l, S x)
{
	if (l == NULL) 
	{
		return -1;
	}
	if (x==l->c.v)
	{
		return 0;
	} 

	int r = _ranglsom(l->suiv, x);
	if (r == -1)
	{
		return -1;
	}  
	else
	{ 
		return r + 1;
	}
}


Strsom * _supkiemelsom(Strsom * l, Nat k)
{
	if (l == NULL) // this should never happen
	{
		return NULL; 
	}
	if (k == 0)
	{
		Strsom *n = l->suiv;
		free(l);
		return n;
	}
	l->suiv = _supkiemelsom(l->suiv, k - 1);
	return l;
}


S _kiemelsom(Strsom * l, Nat k)
{
	if (l == NULL) // this should never happen 
	{ 
		return OMEGA; 
	}
	if (k == 0)
	{
		return l->c.v;
	}
	return _kiemelsom(l->suiv, k - 1);
}


bool _videlsom(Strsom * l) 
{ 
	return l == NULL; 
}


Nat _longueurlsom(Strsom * l)
{
	if (l == NULL)
	{
		return 0;
	}  
	else 
	{
		return 1 + _longueurlsom(l->suiv);
	}
}


void _destroylsom(Strsom *l)
{
	while (l != NULL)
	{
		Strsom *n = l->suiv;
		free(l);
		l = n;
	}
}


// Operations sur le graphe
//////////////////////////////////////////////

Graphe graphe_nouv() 
{ // c'est une nouvelle liste de couples
	return _nouvlsom();
}


Graphe graphe_adjs(Graphe g, S x)
{
	return _adjtetelsom(g, x);
}


Graphe graphe_adja(Graphe g, S u, S v)
{
	Graphe p = _rechlsom(g, u);
	if (_videlsom(p)) // this should not happen
	{
		abort(); 
	} 
	p->c.ls = _adjtetels(p->c.ls, v);
	return g;
}


Graphe graphe_sups(Graphe g, S x)
{
	int r = _ranglsom(g, x);
	if (r == -1) // this should not happen
	{
		abort(); 
	} 
	return _supkiemelsom(g, (Nat)r);
}


Graphe graphe_supa(Graphe g, S u, S v)
{
	Graphe p = _rechlsom(g, u);
	if (_videlsom(p)) // this should not happen
	{
		abort();
	} 

	int r = _rangls(p->c.ls, v);
	if (r==-1) // this should not happen
	{
		abort(); 
	}
	p->c.ls = _supkiemels(p->c.ls, (Nat)r);
	return g;
}


bool graphe_exs(Graphe g, S x)
{
	Graphe p = _rechlsom(g, x);
	return (!_videlsom(p));
}


bool graphe_exa(Graphe g, S u, S v)
{
	Graphe p = _rechlsom(g, u);
	if (_videlsom(p))
	{
		return false;
	}
	return _rangls(p->c.ls, v) != -1;
}


Nat graphe_de(Graphe g, S x)
{
	Graphe p = _rechlsom(g, x);
	if (_videlsom(p))
	{
		return 0;
	} 
	return _longueurls(p->c.ls);
}


// ici on doit parcourir tout le graphe
Nat graphe_di(Graphe g, S x)
{
	Graphe p = g;
	Nat count = 0;
	while (p != NULL)
	{
		if (_rangls(p->c.ls, x) != -1)
		{
			count++;
		}
		p = p->suiv;
	}
	return count;
}


void graphe_free(Graphe g)
{
	Graphe p = g;
	while (p != NULL)
	{
		_destroyls(p->c.ls);
		p = p->suiv;
	}
	_destroylsom(g);
}


ListeSom graphe_lsuccs(Graphe g, S x)
{
	Graphe p = _rechlsom(g, x);
	ListeSom l = _nouvls();
	if (_videlsom(p))
	{
		return l;
	}
	ListeSom arc = p->c.ls;
	//le resultat l est un clone de la liste arc
	while (arc != NULL)
	{
		l = _adjtetels(l, arc->v);
		arc = arc->suc;
	}
	return l;
}


ListeSom graphe_lpreds(Graphe g, S x)
{
	Graphe p = g;
	ListeSom l = _nouvls();
	while (p != NULL)
	{
		if (_rangls(p->c.ls, x) != -1)
		{
			l = _adjtetels(l,p->c.v);
		} 
		p = p->suiv;
	}
	return l;
}


int main()
{
	Graphe g = graphe_nouv();

	for (S i = 1; i <= 6; i++)
	{
		g = graphe_adjs(g, i);
	}

	g = graphe_adja(g, 1, 3);
	g = graphe_adja(g, 1, 6);
	g = graphe_adja(g, 4, 5);
	g = graphe_adja(g, 5, 5);
	g = graphe_adja(g, 6, 1);
	g = graphe_adja(g, 6, 3);

	for (S i = 1; i <= 6; i++)
	{ 
		printf("exa(1,%d)=%s\n", i, graphe_exa(g, 1, i)?"oui":"non");
	}

	for (S i = 1; i <= 6; i++)
	{ 
		printf("sommet %d: de=%d, di=%d\n", i, graphe_de(g, i), graphe_di(g, i));
	}

	/* Cleanup. */
  	graphe_free(g);
  	return 0;
}