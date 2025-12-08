/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include "search.h"
#include <time.h>
#include "permutations.h"
#include <stdlib.h>
#include <stdio.h>


    /*
1. Crear un diccionario de tama˜no N.
2. Crear una permutaci´on de tama˜no N mediante la rutina generate perm.
3. Insertar en el diccionario los elementos de la permutaci´on anterior mediante el uso de la funci´on int massive insertion dictionary .
4. Reservar memoria para la tabla que va a contener las n times*N claves en el rango 1 a N a buscar.

5. Llenar la tabla anterior con las n times*N claves a buscar mediante el uso del generador de claves. (Aviso:
los generadores de claves generan n´umeros de 1 a N, por tanto es importante que vuestras
permutaciones tambi´en sean de los n´umeros de 1 a N).
6. Medir el tiempo (reloj y OBs) que tarda en buscar las n times*N claves almacenadas en la tabla anterior.
7. Rellenar correctamente los campos de la estructura ptime.
8. Liberar memoria y salir.
*/
short average_search_time(pfunc_search method, pfunc_key_generator generator,
char order,
int N,
int n_times,
PTIME_AA ptime){
  PDICT dic = NULL;
  int* perm,*keys = NULL, pos;
  int start,stop,i,ob_current, ob_min=-1, ob_max=-1;
  double time=0, ob_average=0;

  dic = init_dictionary(N, order);
    if (dic == NULL) return ERR;
  
  perm = generate_perm(N);
  if (perm == NULL) {
        free_dictionary(dic);
        return ERR;
    }
  if (massive_insertion_dictionary(dic, perm, N) == ERR) {
        free_dictionary(dic);
        free(perm);
        return ERR;
    }
  if(!(keys = (int*)malloc((n_times*N) * sizeof(int)))){
     free_dictionary(dic);
      free(perm);
    return ERR;
  }
  generator(keys,n_times*N, N);
  start = clock();
    for (i = 0; i < n_times * N; i++) {
        
        ob_current = method(dic->table,0 ,N-1, keys[i], &pos);
        
       
        ob_average += ob_current;
        
        if (ob_min == -1 || ob_current < ob_min) {
            ob_min = ob_current;
        }
        if (ob_max == -1 || ob_current > ob_max) {
            ob_max = ob_current;
        }
    }
    stop = clock();
  time+=((double)(stop - start)) / CLOCKS_PER_SEC;
    ptime->N = N;
    ptime->n_elems = n_times * N;
    ptime->time = ((double)(stop - start)) / CLOCKS_PER_SEC; 
    ptime->average_ob = ob_average / (n_times * N); 
    ptime->min_ob = ob_min;
    ptime->max_ob = ob_max;

    free_dictionary(dic);
    free(perm);
    free(keys);

    return OK;

}


short generate_search_times(pfunc_search method, pfunc_key_generator generator,
char order, char* file, int num_min, int num_max, int incr, int n_times){

  int num, ntimes = (num_max - num_min)/incr + 1;
  PTIME_AA ptimes;

  if(!(ptimes=malloc(sizeof(ptimes[0])*ntimes))){
    return ERR;
  }

  for ( num = num_min; num <= num_max; num += incr)
  {
    if(average_search_time(method, generator, order, num, n_times, ptimes)!=OK){
      free(ptimes);
      return ERR;
    }
  }
  
  if(save_time_table(file, ptimes, n_times)!= OK){
    free(ptimes);
    return ERR;
  }

  free(ptimes);
  return OK;
    
}



/***************************************************/
/* Function: average_sorting_time Date: 10/10/2025 */
/* Authors: Jean del Pozo                          */
/*                                                 */
/* Function that fills the fields of the structure */
/* by computing times and means obtained by the    */
/* sorting function                                */
/*                                                 */
/* Input:                                          */
/* pfunc_sort metodo: pointer to a sorting function*/
/* int n_perms: number of permutations             */
/* int N: number of elements of the permutation    */
/* PTIME_AA ptime: pointer to a time_aa structure  */   
/* Output:                                         */
/* ERR: if there was a problem whit the prameters  */
/* OK: if everything was stored in the structure   */
/*     ptime                                       */   
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{

  int** array_perm;
  int start,stop,i,ob_current, ob_min=0, ob_max=0;
  double time=0, ob_average=0;
  array_perm = generate_permutations(n_perms,N);
  
    
 
  ptime->N=N;
  ptime->n_elems=n_perms;
  start=clock();
  for ( i = 0; i < n_perms; i++)
  {  
    ob_current=metodo(array_perm[i],0,N-1);
    ob_average+=ob_current;
    
    if (i == 0) {            
        ob_min = ob_current;
        ob_max = ob_current;
    } else {
        if (ob_current < ob_min) ob_min = ob_current;
        if (ob_current > ob_max) ob_max = ob_current;
    }
  }
  stop=clock();
  time+=((double)(stop - start)) / CLOCKS_PER_SEC;
  ptime->time=(time+0.)/n_perms;
  ptime->average_ob=ob_average/n_perms;
  ptime->max_ob=ob_max;
  ptime->min_ob=ob_min;
  
  for ( i = 0; i < n_perms; i++)
  {
    free(array_perm[i]);
  }
  free(array_perm); 
  
  return OK;

}

/***************************************************/
/* Function: generate_sorting_times Date:13/10/2025*/
/* Authors: Jean del Pozo                          */
/*                                                 */
/* Function that pases each structure of the array */
/* to the function average_sorting_time to fill    */
/* the fields. Then pases the pointer of the array */ 
/* of structures to save_time_table that will      */
/*                                                 */
/* Input:                                          */
/* pfunc_sort metodo: pointer to a sorting function*/
/* char* file: file used by save_time_table        */
/* int num_min: minimum number of elements to sort */
/* int num_max: maximum number of elements to sort */ 
/* int incr: step to increase the number of        */
/*           elements to sort                      */  
/* int n_perms: number of permutations             */
/* Output:                                         */
/* ERR: if there were problems with parameters or  */
/* mallocs                                         */
/* OK: if the function called saved_time_table to  */
/*     write                                       */   
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{

  int i, num, n_times = (num_max - num_min)/incr + 1;
  PTIME_AA ptimes;

  if(!(ptimes=malloc(sizeof(ptimes[0])*n_times))){
    return ERR;
  }

  for ( num = num_min, i = 0; num <= num_max; i++, num += incr)
  {
    if(average_sorting_time(method,n_perms,num,&ptimes[i])!=OK){
      free(ptimes);
      return ERR;
    }
  }
  
  if(save_time_table(file, ptimes, n_times)!= OK){
    free(ptimes);
    return ERR;
  }

  free(ptimes);
  return OK;
}

/***************************************************/
/* Function: save_time_table Date: 12/10/2025      */
/* Authors: Jean del Pozo                          */
/*                                                 */
/* Function that implements the bubblesort         */
/* algorithm                                       */
/*                                                 */
/* Input:                                          */
/* char* file: file to write values                */
/* PTIME_AA ptime: pointer to an array of          */
/*                 structures                      */
/* int n_times: number of elements in the array    */   
/* Output:                                         */
/* ERR: if there was a problem opening the file    */
/* OK: if writing was succesfully done             */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{

  int i;
  FILE *fp;
  
  fp = fopen(file,"w");
  if(fp==NULL)return ERR;
  for ( i = 0; i < n_times; i++)
  {
    fprintf(fp, "%d\t%.8f\t%.3f\t%.3d\t%.3d\n", 
                ptime[i].N, 
                ptime[i].time, 
                ptime[i].average_ob,
                ptime[i].max_ob,
                ptime[i].min_ob);
  }
  fclose(fp);
  return OK;

}


