#include "cl.h"

int main(int argc, char *argv[])
{

    my_options_t* options = my_program_options_get(argc, argv);
    if (options->success)
    {
        print_options(options);
        exit(EXIT_SUCCESS);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}
