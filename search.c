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
  int* num = NULL;
  num = (int*) malloc(sizeof(int) * size);
  if(num == NULL) return NULL;
    PDICT pdict;
    pdict->n_data = 0;
    pdict->order = order;
    pdict->size = size;
    pdict->table = num;

  return pdict;
}

void free_dictionary(PDICT pdict)
{
  
  free(pdict->table);
  free(pdict);
}

int insert_dictionary(PDICT pdict, int key)
{
  int j, P, U, i;
  int* table;
  char order;
  order = pdict->order;

  if(order == SORTED){
    pdict->table[pdict->n_data] = key;
    table = pdict->table;
    U = pdict->n_data;
    for ( i = 1; i < U; i++)
    {
      j=i-1;
      while (j >= 0 && table[j]>table[i]){
        table[j+1]=table[j]; 
        j--;
      }
    table[j+1]=table[i];
    }
  }else{
    pdict->table[pdict->n_data] = key;
    
  }
  pdict->n_data = pdict->n_data + 1;
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
  return method(pdict->table, 0, pdict->n_data, key, ppos);
}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
	int m, ob = 0;
  *ppos=NOT_FOUND;
  m = floor((F-L)/2);
  ob++;
  if(key == table[m]){
    *ppos = m;
    return;
  }
  if(key > table[m]){
    ob += bin_search(table, m+1, L, key, ppos);
  }else{
    ob += bin_search(table, F, m, key, ppos);
  }
  return ob;
}

int lin_search(int *table,int F,int L,int key, int *ppos)
{
	int length, i, ob = 0;
  *ppos = NOT_FOUND;
  length = L-F;
  for ( i = 0; i < length; i++)
  {
    ob++;
    if(table[i] == key){
      *ppos = i;
    }
  }
  
  return ob;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
	int length, i, ob = 0;
  length = L-F;
  *ppos = NOT_FOUND;
  for ( i = 0; i < length; i++)
  {
    ob++;
    if(table[i] == key){
      if(i>0){
        swap(table[i], table[i-1]);
      }
      *ppos = i;
    }
  }
   
  return ob;
}


