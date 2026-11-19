
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "search.h"


PDICT init_dictionary(int size, char order) {
    PDICT diccionario;

    if (size <= 0 || (order != SORTED && order != NOT_SORTED)) {
        return NULL;
    }

    diccionario = malloc(sizeof(DICT));
    if (diccionario == NULL)  {
        return NULL;
    }

    diccionario->n_data = 0;
    if (strcpy(diccionario->order, order) == NULL) {
        free(diccionario);
        return NULL;
    }
    diccionario->size = size;
    diccionario->table = calloc(size, sizeof(int));
    if (diccionario->table == NULL) {
        free(diccionario);
        return NULL;
    }

    return diccionario;
}


void free_dictionary(PDICT pdict) {
    if (pdict == NULL) {
        return;
    }

    if (pdict->table == NULL) {
        free(pdict);
        pdict = NULL;
        return;
    }

    free(pdict->table);
    pdict->table = NULL;
    free(pdict);
    pdict = NULL;

    return;
}


int insert_dictionary(PDICT dict, int key) {
    int i, operations = 0;

    if (!valid_dictionary(dict) || dict->n_data == dict->size) {
        return ERR;
    }

    if (dict->order == NOT_SORTED) {
        dict->table[dict->n_data] = key;
        dict->n_data++;
        return 1;
    }

    i = dict->n_data;
    while (i > 0) {
        operations++;
        if (dict->table[i - 1] <= key) {
            break;
        }
        dict->table[i] = dict->table[i - 1];
        i--;
    }
    dict->table[i] = key;
    dict->n_data++;

    /* Una insercion valida, incluso en una tabla vacia, cuenta al menos 1. */
    return operations > 0 ? operations : 1;
}




int massive_insertion_dictionary(PDICT pdict, int* keys, int n_keys);





int search_dictionary(PDICT pdict, int key, int* ppos, pfunc_search method);




int bin_search(int* table, int F, int L, int key, int* ppos);




int lin_search(int* table, int F, int L, int key, int* ppos);





int lin_auto_search(int* table, int F, int L, int key, int* ppos);