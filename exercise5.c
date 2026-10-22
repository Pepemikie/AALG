/***********************************************************/
/* Program: exercise5                  Date: 2026          */
/* Authors: Ziqi y Josemi                                  */
/*                                                         */
/* Program that writes in a file the average times         */
/* of the sorting algorithms (InsertSort & BubbleSort)     */
/*                                                         */
/* Input: Command Line                                     */
/* -num_min: lowest number of table elements               */
/* -num_max: highest number of table elements              */
/* -incr: increment                                        */
/* -numP: number of permutations to average                */
/* -outputFile: Output file name base                      */
/* Output: 0: OK, -1: ERR                                  */
/***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sorting.h"
#include "times.h"

#define SEED 12345 /* semilla fija: reproducible */

int main(int argc, char** argv)
{
  int i, num_min = 0, num_max = 0, incr = 0, n_perms = 0;
  char nombre[256] = "";
  char fichero_insert[300] = "";
  char fichero_bubble[300] = "";
  short ret;

  srand(SEED);

  if (argc != 11) {
    fprintf(stderr, "Error in input parameters:\n\n");
    fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
    fprintf(stderr, "\t\t -numP <int> -outputFile <string> \n");
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, "-num_min: lowest number of table elements\n");
    fprintf(stderr, "-num_max: highest number of table elements\n");
    fprintf(stderr, "-incr: increment\n");
    fprintf(stderr, "-numP: number of permutations to average\n");
    fprintf(stderr, "-outputFile: Output file name\n");
    exit(-1);
  }

  printf("Practice number 1, sections 5 & 6\n");
  printf("Done by: Ziqi y Josemi\n");
  printf("Group: 1272/1202\n");
  
  /* check command line */
  for(i = 1; i < argc ; i++) {
    if (strcmp(argv[i], "-num_min") == 0) {
      num_min = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-num_max") == 0) {
      num_max = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-incr") == 0) {
      incr = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      n_perms = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-outputFile") == 0) {
      if (strlen(argv[++i]) > 200) {
        fprintf(stderr, "Output file name too long\n");
        exit(-1);
      }
      strcpy(nombre, argv[i]);
    } else {
      fprintf(stderr, "Wrong parameter %s\n", argv[i]);
      exit(-1);
    }
  }

  /* Formatear nombres de ficheros de salida distintos */
  sprintf(fichero_insert, "insert_%s", nombre);
  sprintf(fichero_bubble, "bubble_%s", nombre);

  /* Medición 1: InsertSort */
  printf("Calculando tiempos para InsertSort...\n");
  srand(SEED); /* mismas permutaciones para ambos metodos */
  ret = generate_sorting_times(InsertSort, fichero_insert, num_min, num_max, incr, n_perms);
  if (ret == ERR) { 
    fprintf(stderr, "Error en la generación de tiempos de InsertSort\n");
    exit(-1); 
  }

  /* Medición 2: BubbleSort */
  printf("Calculando tiempos para BubbleSort...\n");
  srand(SEED); /* misma secuencia de rand() que InsertSort */
  ret = generate_sorting_times(BubbleSort, fichero_bubble, num_min, num_max, incr, n_perms);
  if (ret == ERR) { 
    fprintf(stderr, "Error en la generación de tiempos de BubbleSort\n");
    exit(-1); 
  }

  printf("Correct output: Archivos generados con éxito.\n");
  return 0;
}