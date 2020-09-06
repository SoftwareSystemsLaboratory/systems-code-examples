#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/uio.h>

char *file_data1 = "1234567890";
char *file_data2 = "abcdefghijk";
char *file_data3 = "lmnopqrstuvwxyz";
const char *file_name = "temp.dat";

int main(int argc, char* argv[]) {

    int fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0666);
    if(fd == (-1)) {
        printf("open returned (-1)\n");
        return (-1);
    }

    struct iovec buffers[3];
    buffers[0].iov_base = file_data1;
    buffers[0].iov_len = strlen(file_data1);
    buffers[1].iov_base = file_data2;
    buffers[1].iov_len = strlen(file_data2);
    buffers[2].iov_base = file_data3;
    buffers[2].iov_len = strlen(file_data3);

    int written = writev(fd, buffers, 3);
    if(written == (-1)) {
        printf("writev returned (-1)\n");
        return (-1);
    }
    printf("wrote %d bytes\n", written);

    close(fd);
    return 0;
}


