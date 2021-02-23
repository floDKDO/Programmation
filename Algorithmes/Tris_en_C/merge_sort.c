#include <stdio.h>
#include <stdlib.h>

void tri_fusion(long int* const t, int a, int b)
{
	if (a >= b) 
	{
		return;
	}

	int m = (a + b) / 2;
	tri_fusion(t, a, m);
	tri_fusion(t, m + 1, b);

	long int *tab = (long int *)malloc(sizeof(long int)*(b - a + 1));
	int i = a;
	int j = m + 1;
	int k = 0;
	while (i <= m && j <= b)
	{
		if (t[i]<t[j]) 
		{ 
			tab[k] = t[i]; 
			i++; 
			k++; 
		}
		else 
		{ 
			tab[k] = t[j]; 
			j++; 
			k++; 
		}
	}
	
	while (i <= m)
	{ 
		tab[k] = t[i]; 
		i++; 
		k++; 
	}
	
	while (j <= b) 
	{ 
		tab[k] = t[j]; 
		j++; 
		k++; 
	}
	
	for (i = 0; i<b - a + 1; i++) 
	{
		t[a + i] = tab[i];
	}
	free(tab);
	
}


long int* tri_fusion_exec(size_t size, long int* const array)
{
	tri_fusion(array, 0, size - 1);
	return array;
}


int main()
{
	long int tab[6] = {4, 8, 2, 3, 5, 8};
	size_t taille = 6;
	tri_fusion_exec(taille, tab);
	
	for (size_t i = 0; i < taille; ++i)
    { 
        printf("%ld",tab[i]); 
    }
    // => 234588
    
    return EXIT_SUCCESS;
	
}

// Complexité dans le pire des cas, le cas moyen et le meilleur cas : O(n*log(n))
