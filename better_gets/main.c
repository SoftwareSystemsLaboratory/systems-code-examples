#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_PID (1000)

int childProcesses[MAX_PID];

void addProcess(int childPid) {
    printf("add(%d)\n", childPid);
    for(int i = 0; i < MAX_PID; i++) {
        if(childProcesses[i] == (-1)) {
            childProcesses[i] = childPid;
            printf("added child pid = %d\n", childPid);
            return;
        }
    }
}

void removeProcess(int childPid) {
    printf("remove(%d)\n", childPid);
    for(int i = 0; i < MAX_PID; i++) {
        if(childProcesses[i] == childPid) {
            childProcesses[i] = (-1);
            printf("removed child pid = %d\n", childPid);
        }
    }
}

int countProcesses() {
    int count = 0;
    for(int i = 0; i < MAX_PID; i++) {
        if(childProcesses[i] >= 0) {
            count += 1;
        }
    }
    return count;
}

void clean_up_child_process(int signal_number) {
    printf("SIGCHLD recieved.\n");
    int status;
    pid_t pid;
    while((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if(pid > 0) {
            printf("pid %d exited\n", pid);
            removeProcess((int)pid);
        }
    }
    return;
}

char input[12];

int read_from_stdin() {
    char buffer;
    int error;
    while((error = read(0, &buffer, 1)) == (-1)) {
        if(error == 0) {
            return EOF;
        }
    }
    return buffer;
}

void better_gets(char *buff, int len) {
    int i;
    for(i = 0; i < len-1; i++) {
        int val = read_from_stdin();
        if(val == EOF) {
            break;
        }
        buff[i] = val;
        if(buff[i] == '\n') {
            break;
        }
    }
    buff[i] = (char)0;
    //printf("read: [%s]\n", buff);
}

void parent() {
    printf("parent continuing....\n");
    for(int i = 0; i < 5; i++) {
        printf(">");
        better_gets(&input[0], 12);
        printf("you typed: %s\n", &input[0]);
    }
    while(countProcesses() > 0) {}
    printf("parent exiting\n");
}

void child() {
    printf("child starting.\n");
    sleep(5);
    printf("child exiting.\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv) {
    for(int i = 0; i < MAX_PID; i++) {
        childProcesses[i] = (-1);
    }

    struct sigaction sigchld_action;
    memset (&sigchld_action, 0, sizeof (struct sigaction));
    sigchld_action.sa_handler = &clean_up_child_process;
    sigaction (SIGCHLD, &sigchld_action, NULL);

    for(int i = 0; i < 5; i++) {
        int childProcess = fork();
        if(childProcess == 0) {
            child();
            return 0;
        } else if(childProcess > 0) {
            addProcess(childProcess);
        } else {
            printf("fork failed\n");
        }
    }
    parent();

    return 0;
}


