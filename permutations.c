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
/* Function: random_num Date: 19/11/2026           */
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
/*int random_num(int inf, int sup) {
  unsigned int r, lim, n_inter;

  if (inf < 0 || sup < inf || (sup - inf) > RAND_MAX)
    return ERR;

  n_inter = (unsigned int)(sup - inf) + 1;

  lim = ((unsigned int)RAND_MAX + 1) / n_inter * n_inter;

  do {
    r = (unsigned int)rand();
  } while (r >= lim);
  //esta implementación no es recomendada ya que usa un bucle

  return ((r % n_inter) + inf);
}*/

int random_num(int inf, int sup)
{
  int r;
  r = (rand() / (RAND_MAX + 1.)) * (sup - inf + 1) + inf;
  return r;
}

/***************************************************/
/* Function: generate_permutation Date: 19/11/2026 */
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

int *generate_permutation(int size)
{
  int i, ran, dum;
  int *perm = NULL;

  if (size <= 0)
  {
    return NULL;
  }

  perm = (int *)calloc(size, sizeof(int));
  if (perm == NULL)
  {
    return NULL;
  }

  for (i = 0; i <= size - 1; i++)
  {
    perm[i] = i + 1;
  }

  for (i = 0; i <= size - 1; i++)
  {
    ran = random_num(i, size - 1);
    if (ran == ERR)
    {
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
/* Function: generate_permutations Date: 19/11/2026 */
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
int **generate_permutations(int n_perms, int size)
{
  int i, j;
  int **perms;

  if (n_perms <= 0 || size <= 0)
  {
    return NULL;
  }

  perms = (int **)malloc(n_perms * sizeof(int *));
  if (perms == NULL)
  {
    return NULL;
  }

  for (i = 0; i < n_perms; i++)
  {
    perms[i] = generate_permutation(size);

    if (perms[i] == NULL)
    {
      for (j = 0; j < i; j++)
      {
        free(perms[j]);
      }
      free(perms);
      return NULL;
    }
  }

  return perms;
}