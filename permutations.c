/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"

#include "extern.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *generate_worst_case_mergesort(int N);
void build_worst_case_recursive(int* S, int* T, int low, int high);
/***************************************************/
/* Function: random_num Date: 26/09/2025           */
/* Authors: Jean del Pozo                          */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{

  return rand()/(RAND_MAX+1.) * (sup-inf+1) + inf;

}

/***************************************************/
/* Function: generate_perm Date: 27/09/2025        */
/* Authors: Jose Luis Sanchez                      */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{

  int *perm;
  int j, r;

  perm = (int*)malloc(N*sizeof(int));

  if (perm == NULL) return NULL;

  for (j = 0; j < N; j++) perm[j] = j+1;
  
  for (j = 0; j < N; j++) {
    r = random_num(j,N-1);
    swap(&perm[j], &perm[r]);
  }

  return perm;

}

/***************************************************/
/* Function: generate_permutations Date:30/09/2025 */
/* Authors: Jean del Pozo                          */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{

   int** array;
   int i,j;

   if(!(array=(int**)malloc(n_perms*sizeof(int*)))){
       return NULL;
    }
   for ( i = 0; i < n_perms; i++)
   {
    if(!(array[i]=generate_perm(N))){
      for ( j = i-1; j >= 0; j--)
      {
        free(array[j]);
      }
      free(array);
    return NULL;
    }
   }
   return array;

}

int *generate_worst_case_mergesort(int N) {
  int i;
    int* perm = (int *)malloc(N * sizeof(int));
    int* temp = (int *)malloc(N * sizeof(int)); 

    if (perm == NULL || temp == NULL) {
        free(perm);
        free(temp);
        return NULL;
    }

  
    for (i = 0; i < N; i++) {
        perm[i] = i + 1;
    }

    
    build_worst_case_recursive(perm, temp, 0, N - 1);

  
    free(temp);
    return perm;
}

void build_worst_case_recursive(int* S, int* T, int low, int high) {
    if (low >= high) {
        return; 
    }

    int mid = (low + high) / 2;
    int i, k, j;

   
    k = low;
    for (i = low; i <= high; i += 2) {
        T[k++] = S[i];
    }
    
    j = mid + 1;
    for (i = low + 1; i <= high; i += 2) {
        T[j++] = S[i];
    }

    
    for (i = low; i <= high; i++) {
        S[i] = T[i];
    }

   
    build_worst_case_recursive(S, T, low, mid);
    build_worst_case_recursive(S, T, mid + 1, high);
}