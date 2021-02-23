#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long int* tri_a_bulle(size_t size, long int* const array)
{
	int nn = size - 1;
	bool b = true;
	while (b)
	{
		b = false;
		int i;
		for (i = 0; i <= nn - 1; i++)
		{
			if (array[i]>array[i + 1])
			{
				int buff = array[i]; 
				array[i] = array[i + 1]; 
				array[i + 1] = buff;
				b = true;
			}	
		}
		nn--;
	}
	return array;
}


int main()
{
	long int tab[6] = {4, 8, 2, 3, 5, 8};
	size_t taille = 6;
	tri_a_bulle(taille, tab);
	
	for (size_t i = 0; i < taille; ++i)
    { 
        printf("%ld",tab[i]); 
    }
    // => 234588
    
    return EXIT_SUCCESS;
	
}

// Complexité dans le pire cas et le cas moyen : O(n²)
// Complexité dans le meilleur des cas : O(n)

