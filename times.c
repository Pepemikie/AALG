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
#include <stdlib.h>

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime) {
  int ** perms = NULL;
  double average_ob;
  int min_ob, max_ob;
  clock_t ini,fin;
  int ret;
  int i;

  perms = generate_permutations(n_perms, N);
  if (perms == NULL)
    return ERR;

  ini = clock();
  if (ini == (clock_t)-1)
    return ERR;

  for (i = 0; i < n_perms; i++) {
    ret = metodo(perms[i], 0, N-1);
    if (ret == ERR)
      return ERR;
    
    if(ret < min_ob)
      min_ob = ret;
    
    if(ret > max_ob)
      max_ob = ret;

    average_ob += ret/(double)n_perms;
  }
  fin = clock();
  if (fin == (clock_t)-1)
    return ERR;

  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = ((double)(fin - ini) / CLOCKS_PER_SEC) / n_perms;
  ptime->average_ob=average_ob;
  ptime->min_ob=min_ob;
  ptime->max_ob=max_ob;

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
short generate_sorting_times(pfunc_sort method, char* file,
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

    for (i = 0; i < num; i++) {
        if (average_sorting_time(method, n_perms, num_min + i * incr, &times[i]) == ERR) {
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
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *fp;
  int i;
  fp=fopen(file,"w");
  if(fp==NULL){
    return ERR;
  }

  for ( i = 0; i < n_times; i++)
  {
    if(fprintf(fp,"%d %lf %d %d %d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].min_ob, ptime[i].max_ob) < 0) {
      fclose(fp);
      return ERR;
    } 
  }
  fclose(fp);
  return OK;
}


