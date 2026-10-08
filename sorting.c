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

/***************************************************/
/* Function: InsertSort    Date: 05/10/2026        */
/* Your comment                                    */
/***************************************************/
int InsertSort(int* array, int ip, int iu) {
  int i, j;
  int aux, cont = 0;
  if (array == NULL || ip < 0 || iu < 0 || iu < ip) {
    return ERR;
  }
  for (i = ip + 1; i <= iu; i++) {
    aux = array[i];
    j = i - 1;
    cont++;
    while (j >= ip && array[j] > aux) {
      array[j + 1] = array[j];
      j--;
    }
    array[j + 1] = aux;
  }
  return cont;
}


/***************************************************/
/* Function: SelectSort    Date: 05/10/2026        */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu) {
  int flag = 1;
  int i = iu, j;
  if (array == NULL || ip < 0 || iu < 0) {
    return ERR;
  }
  while (flag == 1 && i >= ip + 1) {
    flag = 0;
    for (j = ip; j <= i-1; j++) {
      if (array[j] > array[j + 1]) {
        /*swap(array[j], array[j + 1]);*/
        flag = 1;
      }
    }
    i--;
  }
  return j;
}






