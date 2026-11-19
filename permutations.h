#ifndef PERMUTATIONS_H_
#define PERMUTATIONS_H_

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

void swap(int *a, int *b);
int* generate_permutation(int size);
int** generate_permutations(int n_perms, int size);

#endif
