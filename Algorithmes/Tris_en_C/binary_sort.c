#include <stdio.h>

  
int binarySearch(long int* const tab, int min, int max, int val) 
{ 
    if (min >= max)
    {
        return min;
    }
  
    int milieu = (min + max) / 2; 
  
    if(tab[milieu] < val)
    {
        return binarySearch(tab, milieu + 1, max, val); 
    }
    else
    {
        return binarySearch(tab, min, milieu, val);
    }
} 

void inserer(long int* const tab, int n, int pos, int x)
{
    int j;
    for (j = n; j >= pos; j--) 
    { 
        tab[j] = tab[j - 1]; 
    } 
    tab[pos] = x;
}
  
long int* tri_insertion_dichotomique(long int* const tab, size_t n) 
{ 
    int pos;
    int j;
    int val; 
    size_t i;
    for (i = 0; i < n; ++i) 
    { 
        pos = binarySearch(tab, 0, i, tab[i]); 
        inserer(tab, i, pos, tab[i]);
    } 
    return tab;
} 
  
// Driver program to test above function 
int main() 
{ 
    long int tab[6] = {4, 8, 2, 3, 5, 8};
    size_t taille = 6;
    tri_insertion_dichotomique(tab, taille); 
  
    for (size_t i = 0; i < taille; ++i)
    { 
        printf("%ld",tab[i]); 
    }
    // => 234588
  
    return EXIT_SUCCESS;
} 


// Complexité dans le pire des cas et le cas moyen : O(n²)
// Complexité dans le meilleur des cas : O(n*log(n))
