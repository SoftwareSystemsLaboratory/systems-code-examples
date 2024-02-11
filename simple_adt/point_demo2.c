#include <stdio.h>
#include <stdlib.h>

#include "point.h"

int main(int argc, char *argv[]) {
    point_t *p1 = point_allocate();
    point_t *p2 = point_allocate();

    point_new(p1);
    point_init(p1, 3.0, 0);
    point_new(p2);
    point_init(p2, 0, 4.0);

    printf("p1 = ");
    point_print(p1, stdout);
    printf(" p2 = ");
    point_print(p2, stdout);
    printf(" distance = %lf\n", point_distance(p1, p2));
}
