#include <stdio.h>
#include <stdlib.h>

#include "rational.h"

int main(int argc, char *argv[]) {
    rational_t r1, r2, r3, result;

    rational_init(&r1, 25, 75);
    rational_init(&r2, -100, 200);
    rational_init(&r3, -100, -200);

    printf("r1 = ");
    rational_print(&r1, stdout, 0);
    printf(" r2 = ");
    rational_print(&r2, stdout, 0);
    printf(" r3 = ");
    rational_print(&r2, stdout, 1);

    printf("r1 + r2 = ");
    rational_add(&r1, &r2, &result);
    rational_print(&result, stdout, 1);

    printf("r1 - r2 = ");
    rational_subtract(&r1, &r2, &result);
    rational_print(&result, stdout, 1);

    printf("r1 * r2 = ");
    rational_multiply(&r1, &r2, &result);
    rational_print(&result, stdout, 1);

    printf("r1 / r2 = ");
    rational_divide(&r1, &r2, &result);
    rational_print(&result, stdout, 1);

    rational_init(&result, 1, 1);
    for (int i = 0; i < 64; i++) {
        printf("r1^%d = ", i);
        if (result.valid)
            rational_print(&result, stdout, 1);
        else {
            rational_print(&result, stdout, 0);
            printf(" [underflow]\n");

        }
        rational_multiply(&result, &r1, &result);
    }
}
