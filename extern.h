#ifndef EXTERN_H
#define EXTERN_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

void swap(int* a, int* b);

#endif