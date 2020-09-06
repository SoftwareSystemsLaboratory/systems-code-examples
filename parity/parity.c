#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

size_t parityWrite(
    int fd0, int fd1, int fd2,
    const void *buf0, const void *buf1,
    size_t count) {
    for(size_t i = 0; i < count; i++) {
        char byte0 = ((char*)buf0)[i];
        char byte1 = ((char*)buf1)[i];
        char parity = byte0 ^ byte1;
        write(fd0, &byte0, sizeof(char));
        write(fd1, &byte1, sizeof(char));
        write(fd2, &parity, sizeof(char));
    }
    return count;
}

size_t parityRead(int fd0, int fd1, void *buf, size_t count) {
    char *buff0 = (char*)malloc(count);
    char *buff1 = (char*)malloc(count);
    char *buff = (char*)buf;
    read(fd0, buff0, count);
    read(fd1, buff1, count);
    for(size_t i = 0; i < count; i++) {
        buff[i] = buff0[i] ^ buff1[i];
    }
    return count;
}

int main(int argc, char** argv) {
    int fd0 = open("f0", O_CREAT|O_TRUNC|O_RDWR, 0666);
    int fd1 = open("f1", O_CREAT|O_TRUNC|O_RDWR, 0666);
    int fd2 = open("f2", O_CREAT|O_TRUNC|O_RDWR, 0666);

    const char* msg0 = "hello world\n";
    const char* msg1 = "testing 123\n";

    parityWrite(fd0,fd1,fd2,msg0,msg1,strlen(msg0)+1);

    close(fd0);
    close(fd1);
    close(fd2);

    unlink("f1");

    fd0 = open("f0", O_RDWR, 0666);
    fd2 = open("f2", O_RDWR, 0666);

    size_t msgSize = sizeof(char)*strlen(msg0)+1;
    char *buff = (char*)malloc(msgSize);

    parityRead(fd0, fd2, buff, msgSize);

    printf("f1 contents are = %s\n", buff);

    close(fd0);
    close(fd2);

    free(buff);

    unlink("f0");
    unlink("f2");

    return 0;
}
