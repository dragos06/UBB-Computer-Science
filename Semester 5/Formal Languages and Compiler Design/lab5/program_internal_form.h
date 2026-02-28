#ifndef PROGRAM_INTERNAL_FORM_H
#define PROGRAM_INTERNAL_FORM_H

typedef struct {
    char* token;
    int index;
} PIFEntry;

typedef struct {
    PIFEntry* entries;
    int size;
    int capacity;
} PIF;

void init_PIF(PIF* pif);

void add_to_PIF(PIF* pif, const char* token, int index);

void print_PIF(const PIF* pif);

void free_PIF(PIF* pif);

#endif