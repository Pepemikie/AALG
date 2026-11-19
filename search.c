
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "search.h"

PDICT init_dictionary(int size, char order);




void free_dictionary(PDICT pdict);






int insert_dictionary(PDICT dict, int key);




int massive_insertion_dictionary(PDICT pdict, int* keys, int n_keys);





int search_dictionary(PDICT pdict, int key, int* ppos, pfunc_search method);




int bin_search(int* table, int F, int L, int key, int* ppos);




int lin_search(int* table, int F, int L, int key, int* ppos);






int lin_auto_search(int* table, int F, int L, int key, int* ppos);