/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"
#include <stdio.h>
#include "extern.h"
#include <stdlib.h> 
#include <math.h>
#include <string.h>


/***************************************************/
/* Function: InsertSort Date: 10/10/2025           */
/* Authors: Jose Luis Sanchez                      */
/*                                                 */
/* Function that implements the insertsort         */
/* algorithm                                       */
/*                                                 */
/* Input:                                          */
/* int* array: pointer to an array of integers to  */
/*             sort                                */
/* int ip: index of the first element on the range */
/*         to sort                                 */
/* int iu: index of the last element on the range  */
/*         to sort                                 */   
/* Output:                                         */
/* ERR: if there was a problem with prameters      */
/* int: number of basic operations                 */
/***************************************************/
int InsertSort(int* array, int ip, int iu)
{
  int i = 0, j = 0, ob = 0, key;
  if(!array ||ip>iu) return ERR;
  
  for (i = ip + 1; i <= iu; i++)
  {
    j = i-1;
    key= array[i];
    
    while (j >= ip)
    {
      ob++;
      if (array[j] > key){
        array[j + 1] = array[j];
        j--;
      }else{
        break;
      }
    }
    array[j+1] = key;
  }
  return ob;
}


/***************************************************/
/* Function: BubbleSort Date: 9/10/2025            */
/* Authors: Jose Luis Sanchez                      */
/*                                                 */
/* Function that implements the bubblesort         */
/* algorithm                                       */
/*                                                 */
/* Input:                                          */
/* int* array: pointer to an array of integers to  */
/*             sort                                */
/* int ip: index of the first element on the range */
/*         to sort                                 */
/* int iu: index of the last element on the range  */
/*         to sort                                 */   
/* Output:                                         */
/* ERR: if there was a problem with parameters     */
/* int: number of basic operations                 */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
  int flag = 1, i = iu, j = 0, ob = 0;
  
  if(!array ||ip>iu){
    return ERR;
  }
  while (flag == 1 && i >= ip)
  {
    flag = 0;
    for (j = ip; j < i; j++)
    {
      ob++;
      if (array[j] > array[j+1])
      {
        swap(&array[j], &array[j+1]);
        flag = 1;
      }
    }
    i--;
  }
  return ob;
}


int quicksort(int* tabla, int ip, int iu){
  int pos, ob=0;
  
  if(ip > iu) return ERR;
  else if(ip == iu) return OK;
  else{
    ob += partition(tabla, ip, iu, &pos);
    if(ip < pos-1){
    ob += quicksort(tabla, ip, pos-1);
    }
    if( pos+1 < iu){
    ob +=  quicksort(tabla, pos+1, iu);
    }
  }
  return ob;
}


int partition(int* tabla, int ip, int iu, int *pos){
  int m, k, i, ob = 0;
  ob += median(tabla, ip, iu, pos);
  k = tabla[*pos];
  swap(&tabla[ip], &tabla[*pos]);
  m = ip;

  for (i = ip+1; i <= iu; i++)
  {
      ob++;
      if(tabla[i] < k){
        m++;
        swap(&tabla[i], &tabla[m]);
      }
  }
  swap(&tabla[ip], &tabla[m]);
  *pos = m;
  return ob;
}

int median(int *tabla, int ip, int iu,int *pos){
  if(!tabla || ip>iu || !pos)return ERR;
  *pos = ip;
  return 0;
}

int median_avg(int *tabla, int ip, int iu, int *pos){
  if(!tabla || ip>iu || !pos)return ERR;
  *pos = (ip + iu)/2;
  return 0;
}

int median_stat(int *tabla, int ip, int iu, int *pos){
    int ob = 0;
    ob++;
    if(tabla[ip] > tabla[iu]){
       ob++;
      if(tabla[(ip+ iu)/2] > tabla[ip]){
        *pos = ip;
        return ob;
      }else{
         ob++;
        if(tabla[iu] > tabla[(ip+ iu)/2]){
          *pos = iu;
          return ob;
        }else{
          *pos = (ip+ iu)/2;
          return ob;
        }
      }
    }else{
       ob++;
      if(tabla[(ip+ iu)/2 ] > tabla[iu]){
        *pos = (ip+ iu)/2;
        return ob;
      }else{
        ob++;
        if(tabla[ip] > tabla[(ip+ iu)/2 ]){
          *pos = iu;
          return ob;
        }else{
          *pos = (ip+ iu)/2;
          return ob;
        }
      }
    }
  }
  


int mergesort(int* tabla, int ip, int iu){
  int m, ob=0;
  if(ip > iu) return ERR;
  else if(ip == iu) return OK;
  else{
    m = (int)floor((ip + iu)/2);
    ob += mergesort(tabla, ip, m);
    ob += mergesort(tabla,  m + 1, iu);
    ob += merge(tabla, ip, iu,m );
    return ob;
  }

}



int merge(int* tabla, int ip, int iu, int imedio){
  int *aux, i,j,k=0, ob = 0;
  if(!(aux = (int*)malloc((iu - ip + 1) * sizeof(int)))){
    return ERR;
  }
  
  for ( i = ip, j = imedio + 1; i <= imedio && j <= iu; k++)
  {
    ob++;
    if(tabla[i] < tabla[j]){
      aux[k] = tabla[i];
      i++;
    } 
    else{
      aux[k] = tabla[j];
      j++;
    }
  }
  
  if(i > imedio){
    while(j <= iu){
      aux[k] = tabla[j];
      j++,k++;
    }
  }else if(j > iu){
      while(i <= imedio){
        aux[k] = tabla[i];
        i++,k++;
      }
  }

  memcpy(&tabla[ip], aux, (iu - ip + 1) * sizeof(int));

  
  free(aux);
  
  return ob;
  
}