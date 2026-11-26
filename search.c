/**
 * @brief Fichero search.c
 * @author Ziqi Zhoulin y José Miguel Romero Oubiña
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "search.h"

/* Initializes a dictionary with the requested capacity and sorting policy. */
PDICT init_dictionary(int size, char order) {
    PDICT diccionario = NULL;

    if (size <= 0 || (order != SORTED && order != NOT_SORTED)) {
        return NULL;
    }

    diccionario = calloc(1, sizeof(DICT));
    if (diccionario == NULL)  {
        diccionario = NULL;
        return NULL;
    }

    diccionario->n_data = 0;
    diccionario->order = order;
    diccionario->size = size;

    diccionario->table = calloc(size, sizeof(int));
    if (diccionario->table == NULL) {
        free(diccionario);
        diccionario = NULL;
        return NULL;
    }

    return diccionario;
}

/* Releases the memory allocated for a dictionary. */
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

/* Inserts a key into the dictionary. */
int insert_dictionary(PDICT dict, int key) {
    int i = 0;
    int operations = 0;

    if ((dict == NULL) || (dict->n_data == dict->size)) {
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

    if (operations > 0) {
        return operations;
    }

    return 1;
}

/* Inserts an array of keys into the dictionary in sequence. */
int massive_insertion_dictionary(PDICT pdict, int* keys, int n_keys) {
    int i = 0;
    int operation = 0;
    int num_operations = 0;

    if (pdict == NULL || keys == NULL || n_keys <= 0) {
        return ERR;
    }

    for (i = 0; i < n_keys; i++) {
        operation = insert_dictionary(pdict, keys[i]);
        if (operation == ERR) {
            return ERR;
        }
        num_operations += operation;
    }
    return num_operations;
}

/* Searches for a key in the dictionary using a caller-provided search method. */
int search_dictionary(PDICT pdict, int key, int* ppos, pfunc_search method) {
    int operations = 0;

    if (pdict == NULL || ppos == NULL || method == NULL) {
        return ERR;
    }

    if (pdict->n_data == 0) {
        *ppos = NOT_FOUND;
        return 1;
    }

    operations = method(pdict->table, 0, pdict->n_data - 1, key, ppos);
    if (operations == ERR) {
        return ERR;
    }

    if (operations > 0) {
        return operations;
    }

    return 1;
}

/* Performs a binary search in a sorted table. */
int bin_search(int* table, int F, int L, int key, int* ppos) {
    int middle = 0;
    int operations = 0;

    if (table == NULL || F < 0 || L < 0 || L < F || ppos == NULL) {
        return ERR;
    }

    while (F <= L) {
        middle = (F + L) / 2;
        operations++;
        if (table[middle] == key) {
            *ppos = middle;
            return operations;
        } else if (table[middle] < key) {
            F = middle + 1;
        } else {
            L = middle - 1;
        }
    }

    *ppos = NOT_FOUND;
    return operations;
}

/* Performs a linear search in a table interval. */
int lin_search(int* table, int F, int L, int key, int* ppos) {
    int i = 0;
    int operations = 0;

    if (table == NULL || F < 0 || L < 0 || L < F || ppos == NULL) {
        return ERR;
    }
    for (i = F; i < L; i++) {
        operations ++;
        if (table[i] == key) {
            *ppos = i;
            return operations;
        }
    }
    *ppos = NOT_FOUND;
    return ERR;
}

/* Performs a linear search that moves a found key one position closer to the front. */
int lin_auto_search(int* table, int F, int L, int key, int* ppos) {
    int i = 0;
    int closer = 0;
    int operations = 0;

    if (table == NULL || F < 0 || L < 0 || L < F || ppos == NULL) {
        return ERR;
    }

    for (i = F; i < L; i++) {
        operations ++;
        if (table[i] == key) {
            closer = table[i];
            table[i] = table[i - 1];
            table[i-1] = closer;
            *ppos = (i-1);
            return operations;
        }
    }
    *ppos = NOT_FOUND;
    return ERR;
}