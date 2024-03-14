#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (pid == 0) {
        exit(0);    //child process exits normally
    }
    int status;
    wait(&status); // wait for child to exit
    printf("status = %d\n", status);
    if (WIFEXITED(status)) {
        printf("normal exit. exit code = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal termination, signal number = %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
    }
}


