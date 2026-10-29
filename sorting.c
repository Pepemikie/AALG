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
#include <stdlib.h>

/***************************************************/
/* Function: InsertSort    Date: 05/10/2026        */
/* Authors: Ziqi y Josemi                          */
/* Ordena de menor a mayor array[ip..iu] por       */
/* insercion. Devuelve ERR o el numero de          */
/* ejecuciones de la OB (array[j] > aux).          */
/***************************************************/

int InsertSort(int *array, int ip, int iu)
{
  int i, j;
  int aux, cont = 0;
  if (array == NULL || ip < 0 || iu < 0 || iu < ip)
  {
    return ERR;
  }
  for (i = ip + 1; i <= iu; i++)
  {
    aux = array[i];
    j = i - 1;
    while (j >= ip)
    {
      cont++;
      if (array[j] > aux)
      {
        array[j + 1] = array[j];
        j--;
      }
      else
      {
        break;
      }
    }
    array[j + 1] = aux;
  }
  return cont;
}

/***************************************************/
/* Function: BubbleSort    Date: 05/10/2026        */
/* Authors: Ziqi y Josemi                          */
/* Ordena de menor a mayor array[ip..iu] por       */
/* burbuja con parada anticipada. Devuelve ERR o   */
/* el numero de ejecuciones de la OB               */
/* (array[j] > array[j+1]).                        */
/***************************************************/

int BubbleSort(int *array, int ip, int iu)
{
  int flag = 1;
  int i = iu, j;
  int cont = 0, aux;

  if (array == NULL || ip < 0 || iu < 0 || iu < ip)
    return ERR;

  while (flag == 1 && i >= ip + 1)
  {
    flag = 0;
    for (j = ip; j <= i - 1; j++)
    {
      cont++;
      if (array[j] > array[j + 1])
      {
        aux = array[j];
        array[j] = array[j + 1];
        array[j + 1] = aux;
        flag = 1;
      }
    }
    i--;
  }

  return cont;
}

/***************************************************/
/* Function:  MergeSort    Date: 22/10/2026        */
/* Authors: Ziqi y Josemi                          */
/***************************************************/

int MergeSort(int *array, int ip, int iu)
{

  int im, c1, c2, c3;

  if (array == NULL || ip < 0 || iu < 0 || iu < ip)
    return ERR;

  if (iu == ip)
  {
    return 0;
  }

  im=(ip+iu)/2;
  
  c1 = MergeSort(array, ip, im);
  if (c1 == ERR)
    return ERR;

  c2 = MergeSort(array, im + 1, iu);
  if (c2 == ERR)
    return ERR;

  c3 = merge(array, ip, iu, im);
  if (c3 == ERR)
    return ERR;

  return c1 + c2 + c3;
}

/***************************************************/
/* Function:  merge        Date: 22/10/2026        */
/* Authors: Ziqi y Josemi                          */
/***************************************************/
int merge(int *array, int ip, int iu, int im)
{

  int *parray = NULL;
  int i = ip, j = im + 1, k = 0, cont = 0;

  if (array == NULL || ip < 0 || iu < 0 || iu < ip){
    return ERR;
  }

  parray = malloc((iu - ip + 1) * sizeof(int));
  if (parray == NULL)
  {
    fprintf(stderr, "merge: error de reserva de memoria\n");
    return ERR;
  }

  while (i <= im && j <= iu)
  {
    cont++;
    if (array[i] < array[j])
    {
      parray[k++] = array[i++];
    }
    else
    {
      parray[k++] = array[j++];
    }
  }

  while (i <= im)
  {
    parray[k++] = array[i++];
  }
  while (j <= iu)
  {
    parray[k++] = array[j++];
  }

  for (i = 0; i < k; i++)
  {
    array[ip + i] = parray[i];
  }

  free(parray);
  return cont;
}

/***************************************************/
/* Function: QuickSort     Date: 22/10/2026        */
/* Authors: Ziqi y Josemi                          */
/***************************************************/
short QuickSort_min(int *array, int ip, int iu)
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
  if(middle == -1) {
    return ERR;
  }
  if (ip < middle -1) {
    QuickSort_min(array, ip, middle-1);
  }
  else if (middle +1 < iu) {
    QuickSort_min(array, middle+1, iu);
  }

  return OK;
}

/***************************************************/
/* Function: partition     Date: 22/10/2026        */
/* Authors: Ziqi y Josemi                          */
/***************************************************/
short partition(int *array, int ip, int iu, int *pos, pfunc_pivot pivot)
{
  short M;
  int i;
  if (array == NULL || ip < 0 || iu < 0 || pos == NULL)
  {
    return 0;
  }

  if (pivot_min(array, ip, iu, pos) != 0)
  {
    return ERR;
  }

  M = array[*pos];

  if(swap(array, ip, *pos) == -1) 
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

  return M;
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