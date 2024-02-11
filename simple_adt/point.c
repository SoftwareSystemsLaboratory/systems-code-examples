#include "point.h"

#include <math.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

point_t *point_allocate() {
    return (point_t *) malloc(sizeof(point_t));
}

void point_new(point_t *point) {
    point->x = 0;
    point->y = 0;
}

void point_init(point_t *point, double x, double y) {
    point->x = x;
    point->y = y;
}

void point_add(point_t *point, point_t *another) {
    point->x += another->x;
    point->y += another->y;
}

double point_distance(point_t *point, point_t *another) {
    double x0 = point->x, y0 = point->y;
    double x1 = another->x, y1 = another->y;
    return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}

double point_x(point_t *point) {
    return point->x;
}

double point_y(point_t *point) {
    return point->y;
}

extern void point_print(point_t *point, FILE *stream) {
    fprintf(stream, "point(%lf, %lf)", point->x, point->y);
}

