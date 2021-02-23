#include <stdio.h>
#include <stdlib.h>


void tri_rapide(long int* const t, int a, int b)
{
	if (a >= b) 
	{
		return;
	}

	long int pivot = t[(a+b)>>1];
	int i = a, j = b;
	while (i<=j)
	{
		while (t[i] < pivot) 
		{
			i++;
		}
		while (t[j] > pivot) 
		{
			j--;
		}
		if (i<=j) 
		{ 
			long int buf = t[i]; 
			t[i] = t[j]; 
			t[j] = buf; 
			i++; 
			j--; 
		}
	}
	tri_rapide(t, a, j);
	tri_rapide(t, i, b);
}

long int* tri_rapide_exec(size_t size, long int* const array)
{
	tri_rapide(array, 0, size - 1);
  return array;
}


int main()
{
	long int tab[6] = {4, 8, 2, 3, 5, 8};
	size_t taille = 6;
	tri_rapide_exec(taille, tab);
	
	for (size_t i = 0; i < taille; ++i)
    { 
        printf("%ld",tab[i]); 
    }
    // => 234588
    
    return EXIT_SUCCESS;
	
}

// Complexité dans le pire des cas : O(n²)
// Complexité dans la cas moyen et le meilleur cas : O(n*log(n))
// On peut aussi dire que (en raccourci) que O représente le pire des cas, Ω représente le meilleur des cas et Θ représente le cas moyen.
// => La complexité dans le pire des cas du tri rapide est AU PLUS O(n²)
// => La complexité dans le pire des cas du tri rapide est AU MOINS Ω(n*log(n))
// => La complexité dans le pire des cas du tri rapide est EXACTEMENT Θ(n*log(n))
