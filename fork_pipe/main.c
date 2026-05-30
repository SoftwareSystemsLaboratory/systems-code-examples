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
        int value;
        scanf("%d\n", &value);
        printf("child sent value = %d\n", value);
    } else if (pid == 0)
    {
        dup2(pipe_output, 1);
        close(pipe_input);
        printf("%d\n", 5000);
    } else {
        printf("fork failed!\n");
    }

    return 0;
}
