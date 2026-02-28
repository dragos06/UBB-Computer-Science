#include "fa_constant.h"
#include <ctype.h>

typedef enum {
    Q0,
    Q_SIGN,
    Q_ZERO,
    Q_NONZERO,
    Q_DIGITS,
    DEAD
} State;

bool is_constant(const char* input) {
    State state = Q0;
    int i = 0;
    char c;

    while ((c = input[i]) != '\0') {
        switch (state) {
            case Q0:
                if (c == '+' || c == '-')
                    state = Q_SIGN;
                else if (c == '0')
                    state = Q_ZERO;
                else if (c >= '1' && c <= '9')
                    state = Q_NONZERO;
                else
                    state = DEAD;
                break;

            case Q_SIGN:
                if (c >= '1' && c <= '9')
                    state = Q_NONZERO;
                else
                    state = DEAD;
                break;

            case Q_ZERO:
                state = DEAD;
                break;

            case Q_NONZERO:
                if (isdigit(c))
                    state = Q_DIGITS;
                else
                    state = DEAD;
                break;

            case Q_DIGITS:
                if (isdigit(c))
                    state = Q_DIGITS;
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

    return (state == Q_ZERO || state == Q_NONZERO || state == Q_DIGITS);
}
