#ifndef _BBOPTIONS_H
#define _BBOPTIONS_H

#define NUM_SUPPLIERS 1
#define NUM_CONSUMERS 1
#define SUPPLIER_DELAY 300
#define CONSUMER_DELAY 1000

/* TODO: Add options for these */
#define BB_SIZE 100
#define GEN_COUNT 2000

typedef struct
{
    int no_suppliers;
    int no_consumers;
    int supplier_max_delay_ms;
    int consumer_max_delay_ms;
    int gen_count; /* # generated per supplier */
    int bsize;
} bb_options_t;

extern int bb_options_get(bb_options_t* options, int argc, char **argv);
extern void bb_options_print(bb_options_t* options);

#endif
