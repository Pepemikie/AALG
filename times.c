/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include "permutations.h"
#include <stdlib.h>

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo,
                           int n_perms,
                           int N,
                           PTIME_AA ptime)
{
  int **perms = NULL;
  double average_ob = 0.0;
  int min_ob = 0, max_ob = 0;
  clock_t ini, fin;
  int ret;
  int i, j;

  if (!metodo || n_perms <= 0 || N <= 0 || !ptime)
  {
    return ERR;
  }

  perms = generate_permutations(n_perms, N);
  if (perms == NULL)
    return ERR;

  ini = clock();
  if (ini == (clock_t)-1)
  {
    for (i = 0; i < n_perms; i++)
      free(perms[i]);
    free(perms);
    return ERR;
  }

  for (i = 0; i < n_perms; i++)
  {
    ret = metodo(perms[i], 0, N - 1);
    if (ret == ERR)
    {
      for (j = 0; j < n_perms; j++)
        free(perms[j]);
      free(perms);
      return ERR;
    }
    if (i == 0)
    {
      min_ob = ret;
      max_ob = ret;
    }
    else
    {
      if (ret < min_ob)
        min_ob = ret;
      if (ret > max_ob)
        max_ob = ret;
    }
    average_ob += ret / (double)n_perms;
  }
  fin = clock();
  if (fin == (clock_t)-1)
  {
    for (i = 0; i < n_perms; i++)
      free(perms[i]);
    free(perms);
    return ERR;
  }

  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = ((double)(fin - ini) / CLOCKS_PER_SEC) / n_perms;
  ptime->average_ob = average_ob;
  ptime->min_ob = min_ob;
  ptime->max_ob = max_ob;

  for (i = 0; i < n_perms; i++)
    free(perms[i]);

  free(perms);

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char *file,
                             int num_min, int num_max,
                             int incr, int n_perms)
{
  PTIME_AA times;
  int i, num;
  short ret;

  if (!method || !file || num_min <= 0 || num_max < num_min ||
      incr <= 0 || n_perms <= 0)
    return ERR;

  num = (num_max - num_min) / incr + 1;

  times = malloc(num * sizeof(*times));
  if (times == NULL)
    return ERR;

  for (i = 0; i < num; i++)
  {
    if (average_sorting_time(method, n_perms, num_min + i * incr, &times[i]) == ERR)
    {
      free(times);
      return ERR;
    }
  }

  ret = save_time_table(file, times, num);
  free(times);
  return ret;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
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
    if (fprintf(fp, "%d %d %.9f %.4f %d %d\n", ptime[i].N, ptime[i].n_elems,
                ptime[i].time, ptime[i].average_ob, ptime[i].min_ob,
                ptime[i].max_ob) < 0)
    {
      fclose(fp);
      return ERR;
    }
  }

  if (fclose(fp) != 0)
    return ERR;
  return OK;
}