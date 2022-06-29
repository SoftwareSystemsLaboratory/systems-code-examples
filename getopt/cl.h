#ifndef _CL_H_
#define _CL_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>

typedef struct my_options_t
{
    int how_many;
    int last_n_words;
    int min_length;
    int every_steps;
    int ignore_case;
    int success;
    int print_options;
    int do_timing;
    regex_t regex;

} my_options_t;

extern my_options_t *my_program_options_new();
extern void my_mrogram_options_delete(my_options_t *options);
extern my_options_t* my_program_options_get (int argc, char **argv);
extern void print_options(my_options_t *options);

#endif
