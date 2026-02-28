#include "fa_identifier.h"
#include <ctype.h>
#include <string.h>

typedef enum {
    Q0, Q1, DEAD
} State;

bool is_identifier(const char* input) {
    State state = Q0;
    int i = 0;
    char c;

    while ((c = input[i]) != '\0') {
        switch (state) {
            case Q0:
                if (isalpha(c))
                    state = Q1;
                else
                    state = DEAD;
                break;

            case Q1:
                if (isalpha(c) || isdigit(c) || c == '_')
                    state = Q1;
                else
                    state = DEAD;
                break;
            default:
                state = DEAD;
        }

        if (state == DEAD)
            return false;
        i++;
    }

    return (state == Q1);
}
