/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Jose Miguel y Ziqi Zhoulin
 * Version: 1.0
 * Fecha: 19-11-2026
 *
 */

#include "times.h"
#include "permutations.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>

short average_search_time(pfunc_search method,
                          char order,
                          int size,
                          int n_perms,
                          pfunc_key_generator generator,
                          int n_keys,
                          PTIME_AA ptime)
{
  int **perms = NULL;
  PDICT *dicts = NULL;
  int *keys = NULL;
  short status = ERR;
  int i, j, pos, ret;
  int min_ob = 0, max_ob = 0, first = 1;
  double total_ob = 0.0;
  clock_t ini, fin;

  if (!method || !generator || !ptime || size <= 0 || n_perms <= 0 ||
      n_keys <= 0 || (order != SORTED && order != NOT_SORTED) ||
      n_perms > INT_MAX / n_keys)
    return ERR;

  perms = generate_permutations(n_perms, size);
  if (perms == NULL)
    return ERR;

  dicts = calloc(n_perms, sizeof(*dicts));
  if (dicts == NULL)
    goto cleanup;

  for (i = 0; i < n_perms; i++)
  {
    dicts[i] = init_dictionary(size, order);
    if (dicts[i] == NULL)
      goto cleanup;
    if (massive_insertion_dictionary(dicts[i], perms[i], size) == ERR)
      goto cleanup;
  }

  keys = malloc(n_keys * sizeof(*keys));
  if (keys == NULL)
    goto cleanup;
  generator(keys, n_keys, size);

  ini = clock();
  if (ini == (clock_t)-1)
    goto cleanup;

  for (i = 0; i < n_perms; i++)
  {
    for (j = 0; j < n_keys; j++)
    {
      ret = search_dictionary(dicts[i], keys[j], &pos, method);
      if (ret == ERR || pos == NOT_FOUND)
        goto cleanup;

      total_ob += ret;
      if (first || ret < min_ob)
        min_ob = ret;
      if (first || ret > max_ob)
        max_ob = ret;
      first = 0;
    }
  }

  fin = clock();
  if (fin == (clock_t)-1)
    goto cleanup;

  ptime->size = size;
  ptime->n_elems = n_perms * n_keys;
  ptime->time = ((double)(fin - ini) / CLOCKS_PER_SEC) / ptime->n_elems;
  ptime->average_ob = total_ob / ptime->n_elems;
  ptime->min_ob = min_ob;
  ptime->max_ob = max_ob;
  status = OK;

cleanup:

  for (i = 0; i < n_perms; i++)
    free(perms[i]);
  free(perms);
  if (dicts != NULL)
  {
    for (i = 0; i < n_perms; i++)
      free_dictionary(dicts[i]);
    free(dicts);
  }
  free(keys);
  return status;
}

short generate_search_times(pfunc_search method,
                            char order,
                            char *file,
                            int min_size,
                            int max_size,
                            int size_incr,
                            int n_perms,
                            pfunc_key_generator generator,
                            int n_keys)
{
  PTIME_AA times;
  int i, n_sizes;
  short ret;

  if (!method || !generator || !file || min_size <= 0 ||
      max_size < min_size || size_incr <= 0 || n_perms <= 0 ||
      n_keys <= 0)
    return ERR;

  n_sizes = (max_size - min_size) / size_incr + 1;

  times = malloc(n_sizes * sizeof(*times));
  if (times == NULL)
    return ERR;

  for (i = 0; i < n_sizes; i++)
  {
    if (average_search_time(method, order, min_size + i * size_incr,
                            n_perms, generator, n_keys,
                            &times[i]) == ERR)
    {
      free(times);
      return ERR;
    }
  }

  ret = save_time_table(file, times, n_sizes);
  free(times);
  return ret;
}

/***************************************************/
/* Function: save_time_table  Date: 09/10/2026     */
/* Authors: Ziqi y Josemi                          */
/* Escribe una fila por tamaño en file:            */
/* Size n_elems time average_ob min_ob max_ob      */
/* Devuelve OK o ERR.                              */
/***************************************************/

short save_time_table(char *file, PTIME_AA ptime, int n_times)
{
  FILE *fp;
  int i;

  if (!file || !ptime || n_times <= 0)
    return ERR;

  fp = fopen(file, "w");
  if (fp == NULL)
    return ERR;

  /* 6 columnas: N n_elems time average_ob min_ob max_ob */
  for (i = 0; i < n_times; i++)
  {
    if (fprintf(fp, "%d %d %.9f %.4f %d %d\n", ptime[i].size, ptime[i].n_elems,
                ptime[i].time, ptime[i].average_ob, ptime[i].min_ob,
                ptime[i].max_ob) < 0)
    {
      if (fclose(fp) != 0)
      {
        return ERR;
      }
      return ERR;
    }
  }

  if (fclose(fp) != 0)
    return ERR;
  return OK;
}