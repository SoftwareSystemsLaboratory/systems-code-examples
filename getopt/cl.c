/*
 * Source: getopt() man page.
 *
 * However, there's more. This example shows how to have
 * different kinds of command-line options. It uses the
 * basic single-letter syntax (e.g. -h, as opposed to --help)
 * which is more than sufficient for my class.
 *
 * I also show how to separate concerns by creating
 * a my_options_t type. After parsing, this structure
 * is populated with the appropriate flags or argumnets
 * to options.
 *
 * TODO: support longer-name options
 * TODO: suppport -h for help and print usage
 */

#include "cl.h"

my_options_t *my_program_options_new()
{
    my_options_t* options =  (my_options_t *) malloc(sizeof(my_options_t));
    options->last_n_words = 100;
    options->how_many = 20;
    options->min_length = 3;
    options->success = 1;
    options->print_options = 0;
    options->every_steps = 1;
    options->ignore_case = 0;
    options->do_timing = 0;
    return options;
}

void my_program_options_delete(my_options_t *options)
{
    free(options);
}

void print_options(my_options_t *options)
{
    if (options->print_options)
    {
        fprintf(stderr, "how_many: %d, last_n_words: %d, min_length: %d, every_steps: %d, ignore_case: %d\n",
                options->how_many, options->last_n_words, options->min_length, options->every_steps, options->ignore_case);
    }
}

my_options_t *my_program_options_get (int argc, char **argv)
{

    /* Initialize my_options_t with defaults */
    my_options_t *options = my_program_options_new();

    int index;
    int c;

    opterr = 0;

    //while ((c = getopt (argc, argv, "abc:")) != -1)
    while ((c = getopt (argc, argv, "l:w:n:s:pct")) != -1)
        switch (c)
        {
        case 'l':
            options->min_length = atoi(optarg);
            break;
        case 'w':
            options->last_n_words = atoi(optarg);
            break;
        case 'n':   /* how many words (top N) */
            options->how_many = atoi(optarg);
            break;
        case 's':
            options->every_steps = atoi(optarg);
            break;
        case 'c':
            options->ignore_case = 1;
            break;
        case 'p':
            options->print_options = 1;
            break;
        case 't':
            options->do_timing = 1;
            break;
        case '?':
            if (optopt == 'w' || optopt == 'l' || optopt == 'n')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
            options->success = 0;
            return options;
        default:
            abort ();
        }

    return options;
}
