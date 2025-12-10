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
#include "permutations.h"
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
  int i;
  int* table = NULL;
  PDICT pdict = NULL;
  pdict = (PDICT) malloc(sizeof(DICT));
  table = (int*) malloc(size * sizeof(int));
  if(table == NULL){
    free(pdict);
    return NULL;
  }
  for (i = 0; i < size; i++)
  {
    table[i] = 0;
  }
    pdict->n_data = 0;
    pdict->order = order;
    pdict->size = size;
    pdict->table = table;
    

  return pdict;
}

void free_dictionary(PDICT pdict)
{
  if (pdict == NULL)
    return;

  if (pdict->table) free(pdict->table);

  free(pdict);
}

int insert_dictionary(PDICT pdict, int key) {
    int  A, j;
    int* table = pdict->table;
    char order = pdict->order;
    table[pdict->n_data] = key;
    pdict->n_data++;

    A = pdict->table[pdict->n_data - 1];
    j = pdict->n_data - 2;

    if (order == SORTED) {
       while (j >= 0 && table[j] > A)
    {
      table[j + 1] = table[j];
      j--;
    }
    table[j + 1] = A;
  }
    
    return OK;
}

int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys)
{
  int i;
	for ( i = 0; i < n_keys; i++)
  {
    insert_dictionary(pdict, keys[i]);
  }
  return OK;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  return method(pdict->table, 0, pdict->n_data - 1, key, ppos);
}


int bin_search(int *table, int F, int L, int key, int *ppos) {
   int ob = 0;
   int mid = (F + L) / 2;

    if (F > L) {
        *ppos = NOT_FOUND;
        return 1;  
    }
    
    ob++;
    if (table[mid] == key) {
        *ppos = mid;
        return ob;   
    }

     
    if (key < table[mid]) {
        return ob + bin_search(table, F, mid - 1, key, ppos);
    } else {
        return ob + bin_search(table, mid + 1, L, key, ppos);
    }
}

int lin_search(int *table, int F, int L, int key, int *ppos)
{
  int i = 0, ob = 0;
  for (i = F; i <= L; i++)
  {
    ob++;
    if (table[i] == key)
    {
      *ppos = i;
      return ob;
    }
  }
  *ppos = NOT_FOUND;
  return ob;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
	int i, ob = 0;
  
  *ppos = NOT_FOUND;
  for ( i = F; i < L; i++)
  {
    ob++;
    if(table[i] == key){
      if (i == 0)
      {
        *ppos = i;
        return ob;
      }
      
        swap(&table[i], &table[i-1]);
        *ppos = i;
        return ob;
    }
  }
   
  return ob;
}


