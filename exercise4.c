/**************************************************/
/* Program: exercise4        Date: 2026           */
/* Authors: Ziqi y Josemi                         */
/*                                                */
/* Program that checks InsertSort and BubbleSort  */
/* on copies of the same random permutation       */
/*                                                */
/* Input: Command Line                            */
/* -size: number of elements of each permutation  */
/* Output: 0: OK, -1: ERR                         */
/**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"
#include "sorting.h"

int main(int argc, char** argv) {
  int tamano = 0, i, j, ret = 0;
  int *perm = NULL, *copia = NULL;

  srand(time(NULL));

  if (argc != 3) {
    fprintf(stderr, "Error in input parameters:\n\n");
    fprintf(stderr, "%s -size <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -size : number of elements in the permutation.\n");
    return 0;
  }
  printf("Practice number 1, section 4 (and 6)\n");
  printf("Done by: Ziqi y Josemi\n");
  printf("Group: 1272/1202\n");

  /* check command line */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-size") == 0) {
      tamano = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Wrong paramenter %s\n", argv[i]);
    }
  }

  perm = generate_perm(tamano);
  if (perm == NULL) { /* error */
    printf("Error: invalid size or out of memory\n");
    exit(-1);
  }

  copia = (int *)malloc(tamano * sizeof(int));
  if (copia == NULL) {
    printf("Error: Out of memory\n");
    free(perm);
    exit(-1);
  }
  for (j = 0; j < tamano; j++)
    copia[j] = perm[j];

  printf("Original:\n");
  for (j = 0; j < tamano; j++)
    printf("%d \t", perm[j]);
  printf("\n");

  ret = MergeSort(copia, 0, tamano - 1);
  if (ret == ERR) {
    printf("Error: Error in MergeSort\n");
    free(perm); free(copia);
    exit(-1);
  }
  printf("MergeSort (OB = %d):\n", ret);
  for (j = 0; j < tamano; j++)
    printf("%d \t", copia[j]);
  printf("\n");

  free(perm);
  free(copia);
  return 0;
}