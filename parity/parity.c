#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

size_t parity_write(
        int fd0, int fd1, int fd2,
        const void *buf0, const void *buf1,
        size_t count) {
    for (size_t i = 0; i < count; i++) {
        char byte0 = ((char *) buf0)[i];
        char byte1 = ((char *) buf1)[i];
        char parity = byte0 ^ byte1;
        write(fd0, &byte0, sizeof(char));
        write(fd1, &byte1, sizeof(char));
        write(fd2, &parity, sizeof(char));
    }
    return count;
}

size_t parity_read(int fd0, int fd1, void *output_buffer, size_t count) {
    char *first_buffer = (char *) malloc(count);
    char *second_buffer = (char *) malloc(count);
    char *recovered_buffer = (char *) output_buffer;
    read(fd0, first_buffer, count);
    read(fd1, second_buffer, count);
    for (size_t i = 0; i < count; i++) {
        recovered_buffer[i] = first_buffer[i] ^ second_buffer[i];
    }
    return count;
}

int main(int argc, char **argv) {
    int fd0 = open("f0", O_CREAT | O_TRUNC | O_RDWR, 0666);
    int fd1 = open("f1", O_CREAT | O_TRUNC | O_RDWR, 0666);
    int fd2 = open("f2", O_CREAT | O_TRUNC | O_RDWR, 0666);

    const char *msg0 = "hello world\n";
    const char *msg1 = "testing 123\n";

    parity_write(fd0, fd1, fd2, msg0, msg1, strlen(msg0) + 1);

    close(fd0);
    close(fd1);
    close(fd2);

    unlink("f1");

    fd0 = open("f0", O_RDWR, 0666);
    fd2 = open("f2", O_RDWR, 0666);

    size_t msg_size = sizeof(char) * strlen(msg0) + 1;
    char *recovered_buffer = (char *) malloc(msg_size);

    parity_read(fd0, fd2, recovered_buffer, msg_size);

    printf("f1 contents are = %s\n", recovered_buffer);

    close(fd0);
    close(fd2);

    free(recovered_buffer);

    unlink("f0");
    unlink("f2");

    return 0;
}
