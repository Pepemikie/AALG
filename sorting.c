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
while (j >= ip) {
      cont++;
      if (array[j] > aux) {
        array[j + 1] = array[j];
        j--;
      } else {
        break;
      }
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
  int cont = 0, aux;

  if (array == NULL || ip < 0 || iu < 0 || iu < ip)
    return ERR;
  
  while (flag == 1 && i >= ip + 1) {
    flag = 0;
    for (j = ip; j <= i - 1; j++) {
      cont++;
      if (array[j] > array[j + 1]) {
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






