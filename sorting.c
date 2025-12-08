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
#include "permutations.h"
#include <stdio.h>
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
int InsertSort(int *array, int ip, int iu)
{
  int i = 0, j = 0, ob = 0, key;
  if (!array || ip > iu)
    return ERR;

  for (i = ip + 1; i <= iu; i++)
  {
    j = i - 1;
    key = array[i];

    while (j >= ip)
    {
      ob++;
      if (array[j] > key)
      {
        array[j + 1] = array[j];
        j--;
      }
      else
      {
        break;
      }
    }
    array[j + 1] = key;
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
int BubbleSort(int *array, int ip, int iu)
{
  int flag = 1, i = iu, j = 0, ob = 0;

  if (!array || ip > iu)
  {
    return ERR;
  }
  while (flag == 1 && i >= ip)
  {
    flag = 0;
    for (j = ip; j < i; j++)
    {
      ob++;
      if (array[j] > array[j + 1])
      {
        swap(&array[j], &array[j + 1]);
        flag = 1;
      }
    }
    i--;
  }
  return ob;
}

/**************************************************/
/*                  QUICKSORT                     */
/**************************************************/

/***************************************************/
/* Función: quicksort Fecha: 29/10/2025            */
/* Autores: Carlos Aguirre, José Luis Sánchez      */
/*                                                 */
/* Función que implementa el algoritmo de          */
/* ordenación rápida (quicksort) de forma          */
/* recursiva.                                      */
/*                                                 */
/* input:                                          */
/* tabla: puntero al array de enteros a ordenar    */
/* int ip: índice del primer elemento del rango    */
/* int iu: índice del último elemento del rango    */
/* output:                                         */
/* ERR: si hubo un problema con los parámetros     */
/* int: número de operaciones básicas realizadas   */
/***************************************************/
int quicksort(int *tabla, int ip, int iu)
{
  int pos, ob = 0;

  if (ip > iu)
    return ERR;
  else if (ip == iu)
    return OK;
  else
  {
    ob += partition(tabla, ip, iu, &pos);
    if(ob == ERR)return ERR;
    if (ip < pos - 1)
    {
      ob += quicksort(tabla, ip, pos - 1);
      if(ob == ERR)return ERR;
    }
    if (pos + 1 < iu)
    {
      ob += quicksort(tabla, pos + 1, iu);
      if(ob == ERR)return ERR;
    }
  }
  return ob;
}
/***************************************************/
/* Función: partition Fecha: 30/10/2025             */
/* Autores: Jean del Pozo                           */
/*                                                  */
/* Función que divide el array en dos partes en     */
/* torno a un pivote seleccionado por la función    */
/* median_stat. Todos los elementos menores que el  */
/* pivote quedan a su izquierda, y los mayores a la */
/* derecha.                                         */
/*                                                  */
/* input:                                           */
/* tabla: puntero al array de enteros               */
/* ip: índice del primer elemento del rango         */
/* iu: índice del último elemento del rango         */
/* pos: puntero donde se almacenará la posición     */
/*           final del pivote                       */
/* output:                                          */
/* ERR: si hubo un problema con los parámetros      */
/* int: número de operaciones básicas realizadas    */
/***************************************************/
int partition(int *tabla, int ip, int iu, int *pos)
{
  int m, k, i, ob = 0;
  ob += median_stat(tabla, ip, iu, pos);
  if (ob == ERR) return ERR;
  k = tabla[*pos];
  swap(&tabla[ip], &tabla[*pos]);
  m = ip;

  for (i = ip + 1; i <= iu; i++)
  {
    ob++;
    if (tabla[i] < k)
    {
      m++;
      swap(&tabla[i], &tabla[m]);
    }
  }
  swap(&tabla[ip], &tabla[m]);
  *pos = m;
  return ob;
}

/***************************************************/
/* Función: median Fecha: 3/11/2025                 */
/* Autores: Jean del Pozo                           */
/*                                                  */
/* Función que selecciona el primer elemento del    */
/* rango como pivote (estrategia simple de mediana).*/
/*                                                  */
/* Entrada:                                         */
/* tabla: array de enteros                          */
/* ip: índice del primer elemento                   */
/* iu: índice del último elemento                   */
/* pos: puntero donde se almacena el pivote         */
/* Salida:                                          */
/* ERR: si hubo un problema con los parámetros      */
/* int: 0 si se ejecuta correctamente               */
/***************************************************/
int median(int *tabla, int ip, int iu, int *pos)
{
  if (!tabla || ip > iu || !pos)
    return ERR;
  *pos = ip;
  return 0;
}
/***************************************************/
/* Función: median_avg Fecha: 4/11/2025            */
/* Autores: Jean del Pozo                          */
/*                                                 */
/* Función que selecciona el elemento medio del    */
/* rango como pivote (promedio entre ip e iu).     */
/*                                                 */
/* input:                                          */
/* tabla: array de enteros                         */
/* ip: índice del primer elemento                  */
/* iu: índice del último elemento                  */
/* pos: puntero donde se almacena el pivote        */
/* output:                                         */
/* ERR: si hubo un problema con los parámetros     */
/* int: 0 si se ejecuta correctamente              */
/***************************************************/
int median_avg(int *tabla, int ip, int iu, int *pos)
{
  if (!tabla || ip > iu || !pos)
    return ERR;
  *pos = (ip + iu) / 2;
  return 0;
}

/***************************************************/
/* Función: median_stat Fecha: 4/11/2025           */
/* Autores: Jean del Pozo                          */
/*                                                 */
/* Función que selecciona la mediana estadística   */
/* entre el primer, el último y el elemento medio  */
/* del rango, para mejorar el equilibrio del       */
/* algoritmo quicksort.                            */
/*                                                 */
/* Entrada:                                        */
/* tabla: array de enteros                         */
/* ip: índice del primer elemento                  */
/* iu: índice del último elemento                  */
/* pos: puntero donde se almacena el pivote        */
/* Salida:                                         */
/* ERR: si hubo un problema con los parámetros     */
/* int: número de operaciones básicas realizadas   */
/***************************************************/
int median_stat(int *tabla, int ip, int iu, int *pos)
{
  int ob = 0;
  ob++;
  if (tabla[ip] > tabla[iu])
  {
    ob++;
    if (tabla[(ip + iu) / 2] > tabla[ip])
    {
      *pos = ip;
      return ob;
    }
    else
    {
      ob++;
      if (tabla[iu] > tabla[(ip + iu) / 2])
      {
        *pos = iu;
        return ob;
      }
      else
      {
        *pos = (ip + iu) / 2;
        return ob;
      }
    }
  }
  else
  {
    ob++;
    if (tabla[(ip + iu) / 2] > tabla[iu])
    {
      *pos = (ip + iu) / 2;
      return ob;
    }
    else
    {
      ob++;
      if (tabla[ip] > tabla[(ip + iu) / 2])
      {
        *pos = iu;
        return ob;
      }
      else
      {
        *pos = (ip + iu) / 2;
        return ob;
      }
    }
  }
}


/**************************************************/
/*                   MERGESORT                    */
/**************************************************/


/***************************************************/
/* Función: mergesort Fecha: 1/11/2025             */
/* Autores: José Luis Sánchez, Jean del Pozo        */
/*                                                  */
/* Función que implementa el algoritmo de ordenación*/
/* mergesort de forma recursiva. Divide el array en */
/* dos mitades, las ordena y luego las combina.     */
/*                                                  */
/* Entrada:                                         */
/* tabla: puntero al array de enteros               */
/* ip: índice del primer elemento del rango         */
/* iu: índice del último elemento del rango         */
/* Salida:                                          */
/* ERR: si hubo un problema con los parámetros      */
/* int: número de operaciones básicas realizadas    */
/***************************************************/
int mergesort(int *tabla, int ip, int iu)
{
  int m, ob = 0;
  if (ip > iu)
    return ERR;
  else if (ip == iu)
    return OK;
  else
  {
    m = (int)floor((ip + iu) / 2);
    ob += mergesort(tabla, ip, m);
    if(ob == ERR)return ERR;
    ob += mergesort(tabla, m + 1, iu);
    if(ob == ERR)return ERR;
    ob += merge(tabla, ip, iu, m);
    if(ob == ERR)return ERR;
    return ob;
  }
}

/***************************************************/
/* Función: merge Fecha: 11/10/2025                 */
/* Autores: José Luis Sánchez, Jean del Pozo        */
/*                                                  */
/* Función que combina dos subarrays ordenados en   */
/* un único array ordenado. Se utiliza en el        */
/* algoritmo mergesort.                             */
/*                                                  */
/* Entrada:                                         */
/* tabla: array que contiene los subarrays          */
/* ip: índice del primer elemento del rango         */
/* iu: índice del último elemento del rango         */
/* imedio: índice que separa ambos subarrays        */
/* Salida:                                          */
/* ERR: si hubo un problema con la memoria          */
/* int: número de operaciones básicas realizadas    */
/***************************************************/
int merge(int *tabla, int ip, int iu, int imedio)
{
  int *aux, i, j, k = 0, ob = 0;
  if (!(aux = (int *)malloc((iu - ip + 1) * sizeof(int))))
  {
    return ERR;
  }

  for (i = ip, j = imedio + 1; i <= imedio && j <= iu; k++)
  {
    ob++;
    if (tabla[i] < tabla[j])
    {
      aux[k] = tabla[i];
      i++;
    }
    else
    {
      aux[k] = tabla[j];
      j++;
    }
  }
  if (i > imedio)
  {
    while (j <= iu)
    {
      aux[k] = tabla[j];
      j++, k++;
    }
  }
  else if (j > iu)
  {
    while (i <= imedio)
    {
      aux[k] = tabla[i];
      i++, k++;
    }
  }
  memcpy(&tabla[ip], aux, (iu - ip + 1) * sizeof(int));
  free(aux);

  return ob;
}