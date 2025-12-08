/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order)
{
  PDICT pdict;
  pdict->size = size;
  pdict->n_data = 0;
  pdict->order = order;

  pdict->table = (int*) malloc(size * sizeof(int));
  if (pdict->table == NULL) {
    free(pdict);
    return NULL;
  }

  return pdict;
}

void free_dictionary(PDICT pdict)
{
  free(pdict->table);
  free(pdict);
}

int insert_dictionary(PDICT pdict, int key)
{
  int i;

  if (pdict->order == NOT_SORTED) {
    pdict->table[pdict->n_data]=key;
    pdict->n_data++;
  } else {
    int U = pdict->n_data;
    int P = 0, j, A, i;
    int *T = pdict->table;

    for (i = P+1; i < U; i++) {
      A = T[U];
      j = U-1;
      while (j >= P && T[j] > A) {
        T[j+1] = T[j];
        j--;
      }
        T[j+1] = A;
    }
  }
  
  return OK;
}

int massive_insertion_dictionary(PDICT pdict,int *keys, int n_keys)
{
  int i;

	for (i = 0; i < n_keys; i++)
  {
    if (insert_dictionary(pdict, keys[i]) != OK)
      return ERR;
  }
  
  return OK;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  return method(pdict->table, 0, pdict->n_data, key, ppos);
}

/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
  int m, ob = 0;
  *ppos = NOT_FOUND;

  if (key == table[m]) {
    *ppos = m;
    return;
  }

  if (key < table[m]) {
    ob++;
    bin_search(table, F, m, key, ppos);
  } else {
    ob++;
    bin_search(table, m + 1, L, key, ppos);
  }

  return ob;
}

int lin_search(int *table,int F,int L,int key, int *ppos)
{
  int length = L-F, i, ob = 0;
  *ppos = NOT_FOUND;

  for (i = 0; i < length; i++)
  {
    ob++;
    if (table[i] == key) {
      *ppos = i;
    }
  }
  
  return ob;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
  int length = L-F, i = 0, ob = 0;
  *ppos = NOT_FOUND;

  for (i = 0; i < length; i++)
  {
    ob++;
    if (table[i] == key) {
      if (i > 0) {
        swap(table[i], table[i-1]);
      }
      *ppos = i;
    }
  }
  
  return ob;
}