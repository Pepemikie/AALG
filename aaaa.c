
#include "sorting.h"
#include <stdlib.h>
/***************************************************/
/* Function: QuickSort     Date: 22/10/2026        */
/* Authors: Ziqi y Josemi                          */
/***************************************************/
int QuickSort_min(int *array, int ip, int iu)
{
  int middle;
  int pos;
  pfunc_pivot funpivot = NULL;

  if (array == NULL)
  {
    return ERR;
  }

  if (ip < 0 || iu < 0 || ip > iu)
  {
    return ERR;
  }

  if (ip == iu)
  {
    return OK;
  }

  middle = partition(array, ip, iu, &pos, funpivot);
  return middle;
}

/***************************************************/
/* Function: partition     Date: 22/10/2026        */
/* Authors: Ziqi y Josemi                          */
/***************************************************/
int partition(int *array, int ip, int iu, int *pos, pfunc_pivot pivot)
{
  int M;
  int i;
  if (array == NULL || ip < 0 || iu < 0 || pos == NULL)
  {
    return 0;
  }

  if (pivot_min(array, ip, iu, pos) != 0)
  {
    return ERR;
  }

  M = array[pos];

  if(swap(array, ip, pos) == -1) 
  {
    return ERR;
  }

  pos = &ip;

  for (i = ip + 1; i < iu; i++) {
    if (array[i] < M) 
    {
      M++;
      if (swap(array, i, M) == -1) 
      {
        return ERR;
      }
    }
  }

  if (swap(array, ip, M) == -1)
  {
    return ERR;
  }

  return 0;
}

/***************************************************/
/* Function: pivot_min     Date: 22/10/2026        */
/* Authors: Ziqi y Josemi                          */
/***************************************************/
int pivot_min(int *array, int ip, int iu, int *pos)
{
  if (array == NULL || ip < 0 || iu < 0 || pos == NULL)
  {
    return -1;
  }

  pos = &ip;

  return 0;
}


/***************************************************/
/* Function: swap          Date: 22/10/2026        */
/* Authors: Ziqi y Josemi                          */
/***************************************************/
int swap(int *array, int p1, int p2) {
  int aux;
  if (array == NULL || p1 < 0 || p2 < 0) 
  {
    return -1;
  }
      
  aux = array[p1];
  array[p1] = array[p2];
  array[p2] = aux;

  return 0;
}