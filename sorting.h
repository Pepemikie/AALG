/**
 *
 * Descripcion: Header file for sorting functions 
 *
 * Fichero: sorting.h
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <time.h>

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

/* type definitions */
typedef int (* pfunc_sort)(int*, int, int);
typedef int (*pfunc_pivot)(int*, int, int, int*);

/* Functions */

int BubbleSort(int* array, int ip, int iu);
int InsertSort(int* array, int ip, int iu);
int MergeSort(int* array, int ip, int iu);
int merge(int* array, int ip, int iu, int im);
int QuickSort_min(int* array, int ip, int iu);
int partition(int* array, int ip, int iu, int* pos, pfunc_pivot pivot);
int pivot_min(int* array, int ip, int iu, int* pos);
int swap(int *array, int p1, int p2);

#endif
