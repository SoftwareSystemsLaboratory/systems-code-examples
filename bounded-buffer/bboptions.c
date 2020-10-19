#include "bboptions.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


int bb_options_get(bb_options_t* options, int argc, char **argv)
{
    int c;
    int digit_optind = 0;

    options->no_suppliers = NUM_SUPPLIERS;
    options->no_consumers = NUM_CONSUMERS;
    options->supplier_max_delay_ms = SUPPLIER_DELAY;
    options->consumer_max_delay_ms = CONSUMER_DELAY;

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"suppliers", required_argument, 0,  's' },
            {"consumers", required_argument,       0,  'c' },
            {"sdelay",    required_argument, 0,  'x' },
            {"cdelay",    required_argument,       0, 'y' },
            {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "abc:d:012",
                        long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 's':
            options->no_suppliers = atoi(optarg);
            break;

        case 'c':
            options->no_consumers = atoi(optarg);
            break;

        case 'x':
            options->supplier_max_delay_ms = atoi(optarg);
            break;

        case 'y':
            options->consumer_max_delay_ms = atoi(optarg);
            break;

        case '?':
            break;

        default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    /*
     * Save these notes from GNU man page.
    if (optind < argc) {
      printf("non-option ARGV-elements: ");
      while (optind < argc)
        printf("%s ", argv[optind++]);
      printf("\n");
    }
    */

}

void bb_options_print(bb_options_t* options) {
    printf("suppliers %d, consumers %d, sdelay %d, cdelay %d\n",
           options->no_suppliers, options->no_consumers, options->supplier_max_delay_ms, options->consumer_max_delay_ms);

}
