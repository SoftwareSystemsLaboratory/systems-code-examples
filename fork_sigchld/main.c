#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int child_exit_status = (-5);

void clean_up_child_process(int signal_number) {
    printf("SIGCHLD recieved.\n");
    int status;
    wait(&status);
    child_exit_status = status;
}

void parent() {
    printf("parent continuing....");
    while(child_exit_status == (-5)) {
        printf("parent waiting...\n");
        sleep(1);
    }
    printf("child exit status = %d\n", child_exit_status);
    printf("parent exiting\n");
}

void child() {
    printf("child starting.\n");
    sleep(5);
    printf("child exiting.\n");
}

int main(int argc, char** argv) {

    struct sigaction sigchld_action;
    memset (&sigchld_action, 0, sizeof (struct sigaction));
    sigchld_action.sa_handler = &clean_up_child_process;
    sigaction (SIGCHLD, &sigchld_action, NULL);

    if(fork() > 0) {
        parent();
    } else {
        child();
    }

    return 0;
}


