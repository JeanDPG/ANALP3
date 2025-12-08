#include "extern.h"
#include <stdlib.h>
#include <stdio.h>

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors: Jose Luis Sanchez                      */
/*                                                 */
/* Function that swaps two integers                */
/*                                                 */
/* Input:                                          */
/* int* a : first integer to swap                  */
/* int* b: second integer to swap                  */
/* Output:                                         */
/* none                                            */ 
/***************************************************/
void swap(int* a, int* b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}