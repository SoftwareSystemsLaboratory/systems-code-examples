#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    int pipes[2];
    pipe(pipes);

    int inputPartOfPipe = pipes[0];
    int outputPartOfPipe = pipes[1];

    int pid = fork();

    if(pid > 0) {	//parent process
        dup2(inputPartOfPipe, 0); // redirect STDIN
        close(outputPartOfPipe);  // close unused half of pipe
        int value;
        scanf("%d\n", &value);
        printf("child sent value = %d\n", value);
    } else if(pid == 0) {	//child process
        dup2(outputPartOfPipe, 1); // redirect STDOUT
        close(inputPartOfPipe);     // close unused half of pipe
        printf("%d\n", 5000);
    } else {
        printf("fork failed!\n");
    }

    //don't worry about closing remaining pipes,
    //process exit does this for us

    return 0;
}


