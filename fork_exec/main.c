#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int pipes[2];
    pipe(pipes);

    int pipe_input = pipes[0];
    int pipe_output = pipes[1];

    int pid = fork();

    if (pid > 0)
    {
        dup2(pipe_input, 0);
        close(pipe_output);

        char *wc_args[] = {"-l", NULL};
        execvp("wc", wc_args);

        fprintf(stderr, "should not be able to reach here!\n");
    } else if (pid == 0)
    {
        dup2(pipe_output, 1);
        close(pipe_input);

        char *echo_args[] = {"-ne", "\"hello\\nworld\\n\"\n", NULL};
        execvp("echo", echo_args);

        fprintf(stderr, "should not be able to reach here!\n");
    } else {
        printf("fork failed!\n");
    }

    return 0;
}
