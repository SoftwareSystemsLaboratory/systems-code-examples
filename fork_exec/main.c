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

    if (pid > 0)    //parent process
    {
        dup2(pipe_input, 0); // redirect STDIN
        close(pipe_output);  // close unused half of pipe

        char *wc_args[] = {"-l", NULL};
        execvp("wc", wc_args);

        fprintf(stderr, "should not be able to reach here!\n");
    } else if (pid == 0)    //child process
    {
        dup2(pipe_output, 1); // redirect STDOUT
        close(pipe_input);     // close unused half of pipe

        char *echo_args[] = {"-ne", "\"hello\\nworld\\n\"\n", NULL};
        execvp("echo", echo_args);

        fprintf(stderr, "should not be able to reach here!\n");
    } else {
        printf("fork failed!\n");
    }

    //don't worry about closing remaining pipes,
    //process exit does this for us

    return 0;
}

