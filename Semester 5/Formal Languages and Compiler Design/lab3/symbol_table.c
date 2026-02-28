#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static SymbolNode* create_node(const char* name, int index) {
    SymbolNode* newNode = (SymbolNode*) malloc(sizeof(SymbolNode));
    newNode->name = strdup(name);
    newNode->index = index;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int insert_symbol(SymbolNode** root, const char* name, int* current_index) {
    if(*root == NULL) {
        *root = create_node(name, *current_index);
        (*current_index)++;
        return (*root)->index;
    }

    int cmp = strcmp(name, (*root)->name);
    if (cmp == 0) {
        return (*root)->index;
    } else if (cmp < 0) {
        return insert_symbol(&((*root)->left), name, current_index);
    } else {
        return insert_symbol(&((*root)->right), name, current_index);
    }   
}

int search_symbol(SymbolNode* root, const char* name) {
    if (root == NULL) return -1;

    int cmp = strcmp(name, root->name);
    if (cmp == 0) return root->index;
    else if (cmp < 0) return search_symbol(root->left, name);
    else return search_symbol(root->right, name);
}

void print_symbol_table(SymbolNode* root) {
    if (root == NULL) return;

    print_symbol_table(root->left);

    printf("Symbol: %s | Index: %d\n", root->name, root->index);

    print_symbol_table(root->right);
}

void free_symbol_table(SymbolNode* root) {
    if (root == NULL) return;
    free_symbol_table(root->left);
    free_symbol_table(root->right);
    free(root->name);
    free(root);
}