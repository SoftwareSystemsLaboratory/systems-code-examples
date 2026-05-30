#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int some_value = 100;
    int pid = fork();
    int fd = open("test_file", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    const char *parent_message = "1111111";
    const char *child_message = "22222222222222\n";

    if (pid > 0) {
        printf("hello from the parent process, chid pid = %d\n", pid);
        sleep(2);
        printf("parent's some_value = %d\n", some_value);
        write(fd, parent_message, strlen(parent_message) * sizeof(char));
    } else if (pid == 0) {
        printf("hello from the child process\n");
        some_value = 200;
        printf("child's some_value = %d\n", some_value);
        write(fd, child_message, strlen(child_message) * sizeof(char));
    } else {
        printf("fork() failed!!\n");
    }

    close(fd);

    return 0;
}

