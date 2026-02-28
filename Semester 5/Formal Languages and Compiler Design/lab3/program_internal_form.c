#include "program_internal_form.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_PIF_CAPACITY 100

void init_PIF(PIF* pif) {
    pif->entries = (PIFEntry*) malloc(INITIAL_PIF_CAPACITY * sizeof(PIFEntry));
    pif->size = 0;
    pif->capacity = INITIAL_PIF_CAPACITY;
}

void add_to_PIF(PIF* pif, const char* token, int index) {
    if (pif->size >= pif->capacity) {
        pif->capacity *= 2;
        pif->entries = realloc(pif->entries, pif->capacity * sizeof(PIFEntry));
    }

    pif->entries[pif->size].token = strdup(token);
    pif->entries[pif->size].index = index;
    pif->size++;
}

void print_PIF(const PIF* pif) {
    printf("\n--- Program Internal Form (PIF) ---\n");
    for (int i = 0; i < pif->size; i++) {
        printf("Token: %s | Identifier: %d\n", pif->entries[i].token, pif->entries[i].index);
    }
}

void free_PIF(PIF* pif) {
    for (int i = 0; i < pif->size; i++) {
        free(pif->entries[i].token);
    }
    free(pif->entries);
    pif->size = 0;
    pif->capacity = 0;
}