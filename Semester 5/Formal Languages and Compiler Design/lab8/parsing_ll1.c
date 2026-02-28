#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* --- CONSTANTS & CONFIGURATION --- */
#define MAX_LINE 512
#define MAX_SYMBOLS 100
#define MAX_SYM_LEN 50
#define MAX_PRODUCTIONS 100
#define MAX_RHS 20
#define MAX_STACK 500
#define EPSILON "epsilon"
#define END_MARKER "$"

/* --- DATA STRUCTURES --- */

// Represents a set of strings (used for NonTerminals, Terminals, First, Follow)
typedef struct {
    char items[MAX_SYMBOLS][MAX_SYM_LEN];
    int count;
} StringSet;

// Represents a single grammar production: A -> X Y Z
typedef struct {
    char lhs[MAX_SYM_LEN];
    char rhs[MAX_RHS][MAX_SYM_LEN];
    int rhs_count;
} Production;

// Represents the Grammar
typedef struct {
    StringSet non_terminals;
    StringSet terminals;
    char start_symbol[MAX_SYM_LEN];
    Production productions[MAX_PRODUCTIONS];
    int prod_count;
} Grammar;

// Represents the LL1 Generator logic
typedef struct {
    StringSet first_set[MAX_SYMBOLS];  // Index corresponds to non_terminals index
    StringSet follow_set[MAX_SYMBOLS]; // Index corresponds to non_terminals index
    
    // Parsing Table: Maps (NonTerm Index, Term Index) -> Production Index (1-based)
    // -1 indicates error/empty
    int table[MAX_SYMBOLS][MAX_SYMBOLS]; 
    bool has_conflicts;
} LL1Gen;

// Tree Node for the output
typedef struct Node {
    char symbol[MAX_SYM_LEN];
    int id;
    struct Node* parent;
    struct Node* children[MAX_RHS];
    int child_count;
    int index_in_siblings; // To help find sibling ID
} Node;

// Queue for BFS (used in printing tree)
typedef struct {
    Node* items[MAX_STACK];
    int front;
    int rear;
} NodeQueue;

/* --- HELPER FUNCTIONS --- */

void error_exit(const char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

// Set operations
void set_add(StringSet* set, const char* val) {
    for (int i = 0; i < set->count; i++) {
        if (strcmp(set->items[i], val) == 0) return;
    }
    strcpy(set->items[set->count++], val);
}

bool set_contains(StringSet* set, const char* val) {
    for (int i = 0; i < set->count; i++) {
        if (strcmp(set->items[i], val) == 0) return true;
    }
    return false;
}

int get_index(StringSet* set, const char* val) {
    for (int i = 0; i < set->count; i++) {
        if (strcmp(set->items[i], val) == 0) return i;
    }
    return -1;
}

void set_union(StringSet* dest, StringSet* src) {
    for (int i = 0; i < src->count; i++) {
        set_add(dest, src->items[i]);
    }
}

// Queue operations
void init_queue(NodeQueue* q) { q->front = 0; q->rear = 0; }
void enqueue(NodeQueue* q, Node* n) { q->items[q->rear++] = n; }
Node* dequeue(NodeQueue* q) { return q->items[q->front++]; }
bool is_empty(NodeQueue* q) { return q->front == q->rear; }

/* --- GRAMMAR FUNCTIONS --- */

void load_grammar(Grammar* g, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) error_exit("Could not open grammar file");

    char line[MAX_LINE];
    bool reading_prods = false;
    g->prod_count = 0;
    g->non_terminals.count = 0;
    g->terminals.count = 0;

    while (fgets(line, sizeof(line), f)) {
        // Trim newline
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;

        if (strncmp(line, "N =", 3) == 0) {
            char* content = strchr(line, '=') + 1;
            char* token = strtok(content, " ");
            while (token) {
                set_add(&g->non_terminals, token);
                token = strtok(NULL, " ");
            }
        } else if (strncmp(line, "E =", 3) == 0) {
            char* content = strchr(line, '=') + 1;
            char* token = strtok(content, " ");
            while (token) {
                set_add(&g->terminals, token);
                token = strtok(NULL, " ");
            }
        } else if (strncmp(line, "S =", 3) == 0) {
            char* content = strchr(line, '=') + 1;
            while (*content == ' ') content++;
            strcpy(g->start_symbol, content);
        } else if (strncmp(line, "P =", 3) == 0) {
            reading_prods = true;
        } else if (reading_prods && strstr(line, "->")) {
            char* sep = strstr(line, "->");
            *sep = 0; // split string
            char* lhs = line;
            char* rhs = sep + 2;

            // Trim LHS
            while (*lhs == ' ') lhs++;
            char* end = lhs + strlen(lhs) - 1;
            while (end > lhs && *end == ' ') *end-- = 0;

            Production* p = &g->productions[g->prod_count++];
            strcpy(p->lhs, lhs);
            p->rhs_count = 0;

            char* token = strtok(rhs, " ");
            while (token) {
                strcpy(p->rhs[p->rhs_count++], token);
                token = strtok(NULL, " ");
            }
        }
    }

    // Auto-detect terminals not in E but in productions (excluding N and epsilon)
    for (int i = 0; i < g->prod_count; i++) {
        for (int j = 0; j < g->productions[i].rhs_count; j++) {
            char* sym = g->productions[i].rhs[j];
            if (strcmp(sym, EPSILON) != 0 && !set_contains(&g->non_terminals, sym)) {
                set_add(&g->terminals, sym);
            }
        }
    }
    
    // Add $ to terminals for parsing table logic
    set_add(&g->terminals, END_MARKER);
    
    fclose(f);
}

/* --- LL1 GENERATION FUNCTIONS --- */

void compute_first_seq(Grammar* g, LL1Gen* gen, char rhs[][MAX_SYM_LEN], int rhs_len, StringSet* result) {
    if (rhs_len == 0) return;

    char* symbol = rhs[0];

    if (strcmp(symbol, EPSILON) == 0) {
        set_add(result, EPSILON);
    } else if (set_contains(&g->terminals, symbol)) {
        set_add(result, symbol);
    } else if (set_contains(&g->non_terminals, symbol)) {
        int idx = get_index(&g->non_terminals, symbol);
        StringSet* first_of_sym = &gen->first_set[idx];
        
        // Add everything from FIRST(symbol) to result
        for(int k=0; k<first_of_sym->count; k++) {
            set_add(result, first_of_sym->items[k]);
        }

        // If epsilon in FIRST(symbol) and more symbols remain, recurse
        if (set_contains(first_of_sym, EPSILON) && rhs_len > 1) {
            // Remove epsilon temporarily (conceptually) for union, then recurse
            // Note: In strict set logic, we add epsilon only if all parts produce epsilon.
            // But here, if we recurse, we are effectively trying to see what comes next.
            // We just need to ensure 'result' eventually has epsilon only if the whole chain is nullable.
            
            // Re-call with rest of sequence
            // We need a temporary set for the recursive call to check nullability
             // Simplified: if epsilon is in current, we continue.
             // The simple way: Remove epsilon from current result, add result of next.
             // Note: Implementing strictly as per python logic:
             // first_result.remove('epsilon') -> done implicitly by not breaking loop if we handled sets differently, 
             // but here we just added it.
             
             // Correct logic for C translation of Python code:
             // Python: first_result.remove('epsilon'); first_result.update(...)
             // Since we use set_add which doesn't remove, we might have added epsilon.
             // We can't easily "remove" from our array-set without shifting.
             // Instead, let's just be careful. 
             // If we recurse, it means we consumed an epsilon. 
             // The final result has epsilon ONLY if the recursion adds it back.
             
             // Trick: If we are going to recurse, we shouldn't have added epsilon from this symbol yet? 
             // Actually, the Python code adds it, then removes it if len > 1.
             // Let's implement a 'remove' helper or just handle it.
             
             // Simple hack for this specific function:
             // If we are recursing, find epsilon index and decrease count (remove it), then recurse.
             for(int z=0; z<result->count; z++) {
                 if(strcmp(result->items[z], EPSILON) == 0) {
                     // Swap with last and decrease count
                     strcpy(result->items[z], result->items[result->count-1]);
                     result->count--;
                     break;
                 }
             }
             
             // Pass pointer to slice of array? No, simpler to pass new array start logic
             // We can't pass pointer arithmetic on 2D array easily. 
             // We construct a temp array or pass index.
             // Let's pass index + 1.
             // We can't change the signature easily, so let's copy the rest to a temp buffer.
             // (Inefficient but safe).
             char temp_rhs[MAX_RHS][MAX_SYM_LEN];
             for(int c=1; c<rhs_len; c++) strcpy(temp_rhs[c-1], rhs[c]);
             compute_first_seq(g, gen, temp_rhs, rhs_len - 1, result);
        }
    }
}

void generate_first(Grammar* g, LL1Gen* gen) {
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < g->prod_count; i++) {
            Production* p = &g->productions[i];
            int lhs_idx = get_index(&g->non_terminals, p->lhs);
            
            StringSet rhs_first; rhs_first.count = 0;
            compute_first_seq(g, gen, p->rhs, p->rhs_count, &rhs_first);
            
            int original_size = gen->first_set[lhs_idx].count;
            set_union(&gen->first_set[lhs_idx], &rhs_first);
            
            if (gen->first_set[lhs_idx].count > original_size) change = true;
        }
    }
}

void generate_follow(Grammar* g, LL1Gen* gen) {
    int start_idx = get_index(&g->non_terminals, g->start_symbol);
    set_add(&gen->follow_set[start_idx], END_MARKER);

    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < g->prod_count; i++) {
            Production* p = &g->productions[i];
            char* lhs = p->lhs;
            int lhs_idx = get_index(&g->non_terminals, lhs);

            for (int j = 0; j < p->rhs_count; j++) {
                char* symbol = p->rhs[j];
                if (set_contains(&g->non_terminals, symbol)) {
                    int sym_idx = get_index(&g->non_terminals, symbol);
                    
                    // Beta is everything after j
                    StringSet beta_first; beta_first.count = 0;
                    // Create temp rhs for beta
                    char beta_rhs[MAX_RHS][MAX_SYM_LEN];
                    int beta_len = 0;
                    for(int k=j+1; k<p->rhs_count; k++) {
                        strcpy(beta_rhs[beta_len++], p->rhs[k]);
                    }
                    compute_first_seq(g, gen, beta_rhs, beta_len, &beta_first);

                    int original_size = gen->follow_set[sym_idx].count;

                    // Add FIRST(beta) - {epsilon}
                    bool epsilon_in_beta = false;
                    for(int k=0; k<beta_first.count; k++) {
                        if(strcmp(beta_first.items[k], EPSILON) == 0) epsilon_in_beta = true;
                        else set_add(&gen->follow_set[sym_idx], beta_first.items[k]);
                    }

                    if (beta_len == 0 || epsilon_in_beta) {
                        set_union(&gen->follow_set[sym_idx], &gen->follow_set[lhs_idx]);
                    }

                    if (gen->follow_set[sym_idx].count > original_size) change = true;
                }
            }
        }
    }
}

void build_parsing_table(Grammar* g, LL1Gen* gen) {
    // Initialize table with -1
    for(int i=0; i<MAX_SYMBOLS; i++)
        for(int j=0; j<MAX_SYMBOLS; j++)
            gen->table[i][j] = -1;
            
    gen->has_conflicts = false;

    for (int i = 0; i < g->prod_count; i++) {
        Production* p = &g->productions[i];
        int lhs_idx = get_index(&g->non_terminals, p->lhs);
        
        StringSet first_alpha; first_alpha.count = 0;
        compute_first_seq(g, gen, p->rhs, p->rhs_count, &first_alpha);
        
        bool epsilon_in_first = false;
        for(int k=0; k<first_alpha.count; k++) {
            char* terminal = first_alpha.items[k];
            if(strcmp(terminal, EPSILON) == 0) {
                epsilon_in_first = true;
                continue;
            }
            
            int term_idx = get_index(&g->terminals, terminal);
            if (term_idx == -1) continue; // Should not happen

            if (gen->table[lhs_idx][term_idx] != -1 && gen->table[lhs_idx][term_idx] != i + 1) {
                printf("  [CONFLICT] Table[%s, %s]: Prod %d vs Prod %d\n", p->lhs, terminal, gen->table[lhs_idx][term_idx], i+1);
                gen->has_conflicts = true;
            } else {
                gen->table[lhs_idx][term_idx] = i + 1;
            }
        }

        if (epsilon_in_first) {
            StringSet* follow = &gen->follow_set[lhs_idx];
            for(int k=0; k<follow->count; k++) {
                char* terminal = follow->items[k];
                int term_idx = get_index(&g->terminals, terminal);
                 if (term_idx == -1) continue;

                if (gen->table[lhs_idx][term_idx] != -1 && gen->table[lhs_idx][term_idx] != i + 1) {
                    printf("  [CONFLICT] Table[%s, %s] (via Follow): Prod %d vs Prod %d\n", p->lhs, terminal, gen->table[lhs_idx][term_idx], i+1);
                    gen->has_conflicts = true;
                } else {
                    gen->table[lhs_idx][term_idx] = i + 1;
                }
            }
        }
    }
}

/* --- PARSER --- */

// Returns dynamic array of ints (production indices), ends with -1
int* parse(Grammar* g, LL1Gen* gen, char** input_seq, int input_len) {
    // Input Stack (Simulated by index in input_seq)
    // Actually, we need to append '$' to input.
    char* input_stack[MAX_STACK];
    for(int i=0; i<input_len; i++) input_stack[i] = input_seq[i];
    input_stack[input_len] = END_MARKER;
    int input_idx = 0;

    // Working Stack
    char* work_stack[MAX_STACK];
    int work_top = 0;
    work_stack[work_top++] = END_MARKER; // Bottom
    work_stack[work_top++] = g->start_symbol; // Top

    // Output
    static int output_prods[MAX_STACK]; // Static buffer for return
    int out_count = 0;

    while (true) {
        char* top_input = input_stack[input_idx];
        char* top_work = work_stack[work_top - 1];

        if (strcmp(top_input, END_MARKER) == 0 && strcmp(top_work, END_MARKER) == 0) {
            output_prods[out_count] = -1; // Terminator
            return output_prods;
        }

        if (strcmp(top_work, top_input) == 0) {
            input_idx++;
            work_top--; // Pop
        } else {
            // It must be a non-terminal
            int nt_idx = get_index(&g->non_terminals, top_work);
            int t_idx = get_index(&g->terminals, top_input);

            if (nt_idx == -1 || t_idx == -1) {
                printf("ERROR: Invalid symbol lookup: Work=%s, Input=%s\n", top_work, top_input);
                return NULL;
            }

            int prod_idx = gen->table[nt_idx][t_idx];
            if (prod_idx == -1) {
                printf("ERROR: Syntax Error at token '%s'. Expected from '%s'\n", top_input, top_work);
                return NULL;
            }

            output_prods[out_count++] = prod_idx;
            Production* p = &g->productions[prod_idx - 1];
            
            work_top--; // Pop LHS
            
            if (strcmp(p->rhs[0], EPSILON) != 0) {
                // Push RHS in reverse
                for (int k = p->rhs_count - 1; k >= 0; k--) {
                    work_stack[work_top++] = p->rhs[k];
                }
            }
        }
    }
}

/* --- TREE BUILDER --- */

// Recursive helper that consumes the iterator (int ptr)
Node* recursive_build_tree(Grammar* g, char* symbol, int* prod_indices_iter) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->symbol, symbol);
    node->child_count = 0;
    node->parent = NULL;
    node->id = 0;
    
    if (set_contains(&g->terminals, symbol) || strcmp(symbol, EPSILON) == 0) {
        return node;
    }

    // Must be non-terminal, consume production
    int prod_idx = *prod_indices_iter;
    *prod_indices_iter = *(prod_indices_iter + 1); // Move pointer? No, array logic.
    // In C, we passed the pointer to the CURRENT position in array. 
    // We need to advance the value the pointer points to? No, pointer to current element.
    // Actually simpler: pass int* current_idx, and access array globally or pass array.
    // Let's refactor signature later. For now, assume prod_indices_iter points to current int in array.
    
    // Actually, let's fix the call:
    // We need to advance the stream. 
    // If we just dereference, we get value. We need to increment the pointer for the NEXT call.
    // BUT, recursive_build is called inside the loop.
    
    // Better signature: Node* build(..., int* prods, int* current_pos)
    return NULL; // Placeholder
}

Node* build_tree_logic(Grammar* g, char* symbol, int* prods, int* pos) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->symbol, symbol);
    node->child_count = 0;
    node->parent = NULL;

    if (set_contains(&g->terminals, symbol) || strcmp(symbol, EPSILON) == 0) {
        return node;
    }
    
    int prod_idx = prods[*pos];
    (*pos)++; // Consume
    
    Production* p = &g->productions[prod_idx - 1];
    
    if (strcmp(p->rhs[0], EPSILON) == 0) {
        Node* child = (Node*)malloc(sizeof(Node));
        strcpy(child->symbol, EPSILON);
        child->child_count = 0; 
        child->parent = node;
        node->children[node->child_count++] = child;
    } else {
        for(int i=0; i<p->rhs_count; i++) {
            Node* child = build_tree_logic(g, p->rhs[i], prods, pos);
            child->parent = node;
            node->children[node->child_count++] = child;
        }
    }
    return node;
}

void print_tree_table(Node* root) {
    // BFS to assign IDs
    NodeQueue q; init_queue(&q);
    enqueue(&q, root);
    int idx = 1;
    
    while(!is_empty(&q)) {
        Node* n = dequeue(&q);
        n->id = idx++;
        for(int i=0; i<n->child_count; i++) {
            n->children[i]->index_in_siblings = i; // Store index for sibling logic
            enqueue(&q, n->children[i]);
        }
    }

    printf("\n%-10s %-20s %-10s %-10s\n", "Index", "Symbol", "Father", "Sibling");
    printf("-------------------------------------------------------\n");

    // BFS again to print
    init_queue(&q);
    enqueue(&q, root);
    while(!is_empty(&q)) {
        Node* n = dequeue(&q);
        
        int father_id = (n->parent) ? n->parent->id : 0;
        int sibling_id = 0;
        
        if (n->parent) {
            int my_idx = n->index_in_siblings;
            if (my_idx + 1 < n->parent->child_count) {
                sibling_id = n->parent->children[my_idx + 1]->id;
            }
        }
        
        printf("%-10d %-20s %-10d %-10d\n", n->id, n->symbol, father_id, sibling_id);
        
        for(int i=0; i<n->child_count; i++) {
            enqueue(&q, n->children[i]);
        }
    }
}

/* --- MAIN HELPERS --- */

int read_file_content(const char* filename, char** buffer) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;
    
    char line[MAX_LINE];
    int count = 0;
    while(fscanf(f, "%s", line) == 1) {
        buffer[count] = (char*)malloc(MAX_SYM_LEN);
        strcpy(buffer[count++], line);
    }
    fclose(f);
    return count;
}

int read_pif_content(const char* filename, char** buffer) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;
    
    char line[MAX_LINE];
    int count = 0;
    while(fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = 0;
        if(strlen(line) == 0) continue;
        
        buffer[count] = (char*)malloc(MAX_SYM_LEN);
        if (strncmp(line, "ID(", 3) == 0) strcpy(buffer[count++], "ID");
        else if (strncmp(line, "CONST(", 6) == 0) strcpy(buffer[count++], "CONST");
        else strcpy(buffer[count++], line);
    }
    fclose(f);
    return count;
}

/* --- MAIN --- */

int main() {
    Grammar g1, g2;
    LL1Gen gen1, gen2;
    char* seq_buffer[MAX_STACK];

    // --- REQUIREMENT 1 ---
    printf("\n========================================\n");
    printf(" REQUIREMENT 1: Seminar Grammar\n");
    printf("========================================\n");

    load_grammar(&g1, "seminar_grammar.txt");
    
    printf(">> Generating FIRST set...\n");
    generate_first(&g1, &gen1);
    printf(">> Generating FOLLOW set...\n");
    generate_follow(&g1, &gen1);
    printf(">> Building Parsing Table...\n");
    build_parsing_table(&g1, &gen1);

    if (gen1.has_conflicts) {
        printf("\n[RESULT] The Seminar Grammar is NOT LL(1). Conflicts found.\n");
    } else {
        printf("\n[RESULT] The Seminar Grammar IS LL(1).\n");
    }

    int seq_len = read_file_content("seq.txt", seq_buffer);
    int* res1 = parse(&g1, &gen1, seq_buffer, seq_len);
    
    if (res1) {
        printf("Parsed successfully! Productions: ");
        for(int i=0; res1[i] != -1; i++) printf("%d ", res1[i]);
        printf("\n");
    }

    // Cleanup buffer
    for(int i=0; i<seq_len; i++) free(seq_buffer[i]);

    // --- REQUIREMENT 2 ---
    printf("\n========================================\n");
    printf(" REQUIREMENT 2: My DSL Grammar\n");
    printf("========================================\n");

    load_grammar(&g2, "my_grammar.txt");
    
    // Clear sets for gen2
    for(int i=0; i<MAX_SYMBOLS; i++) { gen2.first_set[i].count=0; gen2.follow_set[i].count=0; }
    
    printf(">> Generating FIRST set...\n");
    generate_first(&g2, &gen2);
    printf(">> Generating FOLLOW set...\n");
    generate_follow(&g2, &gen2);
    printf(">> Building Parsing Table...\n");
    build_parsing_table(&g2, &gen2);

    if (gen2.has_conflicts) {
        printf("\n[RESULT] My Grammar had conflicts.\n");
    } else {
        printf("\n[RESULT] My Grammar IS LL(1). No conflicts in parsing table.\n");
    }

    int pif_len = read_pif_content("pif.txt", seq_buffer);
    int* res2 = parse(&g2, &gen2, seq_buffer, pif_len);

    if (res2) {
        int pos = 0;
        Node* root = build_tree_logic(&g2, g2.start_symbol, res2, &pos);
        printf("\n[Req 2.c] Father-Sibling Table:\n");
        print_tree_table(root);
    }
    
    // Cleanup buffer
    for(int i=0; i<pif_len; i++) free(seq_buffer[i]);

    return 0;
}