#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct SymbolNode {
    char* name;
    int index;
    struct SymbolNode* left;
    struct SymbolNode* right;
} SymbolNode;

int insert_symbol(SymbolNode** root, const char* name, int* current_index);

int search_symbol(SymbolNode* root, const char* name);

void print_symbol_table(SymbolNode* root);
void free_symbol_table(SymbolNode* root);

#endif