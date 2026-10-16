/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */

#include "permutations.h"
#include <stdlib.h>
#include <stdio.h>
/***************************************************/
/* Function: random_num Date:                      */
/* Authors: Ziqi y Josemi                          */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup) {
  int r;

  if (inf < 0 ||sup < inf || (((sup - inf) - 1) > RAND_MAX))
    return ERR;
  
  r = ((rand() / (RAND_MAX + 1.0)) * (sup - inf + 1) + inf);
    
  return r;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors: Ziqi y Josemi                          */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int N: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int *generate_perm(int N) {
  int i, ran, dum;
  int *perm = NULL;

  if (N <= 0) {
    return NULL;
  }

  perm = (int *)calloc(N, sizeof(int));
  if (perm == NULL) {
    return NULL;
  }

  for (i = 0; i <= N - 1; i++) {
    perm[i] = i + 1;
  }

  for (i = 0; i <= N - 1; i++) {
    ran = random_num(i, N - 1);
    if (ran == ERR) {
      free(perm);
      return NULL;
    }
    dum = perm[ran];
    perm[ran] = perm[i];
    perm[i] = dum;
  }

  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors: Ziqi y Josemi                          */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int **generate_permutations(int n_perms, int N) {
  int i, j;
  int **perms;

  if (n_perms <= 0 || N <= 0) {
    return NULL;
  }

  perms = (int **)malloc(n_perms * sizeof(int *));
  if (perms == NULL) {
    return NULL;
  }

  for (i = 0; i < n_perms; i++) {
    perms[i] = generate_perm(N);

    if (perms[i] == NULL) {
      for (j = 0; j < i; j++) {
        free(perms[j]);
      }
      free(perms);
      return NULL;
    }
  }

  return perms;
}