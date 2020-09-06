#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

const char *file_data = "1234567890abcdefghijklmnopqrstuvwxyz";
const char *file_name = "temp.dat";

int main(int argc, char* argv[]) {

    int fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0666);
    if(fd == (-1)) {
        printf("open returned (-1)\n");
        return (-1);
    }

    size_t length = strlen(file_data);
    size_t offset = 0;
    while(length > 0) {
        size_t written = write(fd, file_data + offset, length);
        if(written == (-1)) {
            printf("write returned (-1)\n");
            return (-1);
        }
        printf("wrote %d bytes\n", written);
        offset += written;
        length -= written;
    }

    if(close(fd) == (-1)) {
        printf("close returned (-1)\n");
        return (-1);
    }

    printf("file contents written.\n");

    fd = open(file_name, O_RDONLY, 0666);
    if(fd == (-1)) {
        printf("open returned (-1)\n");
        return (-1);
    }

    char buffer[5];
    //read in a loop until zero bytes are read
    //zero return value means EOF
    while((length = read(fd, &buffer[0], 5)) != 0) {
        if(length == (-1)) {
            printf("read returned (-1)\n");
            return (-1);
        }
        write(1, &buffer[0], length);
    }
    printf("\n");

    if(close(fd) == (-1)) {
        printf("close returned (-1)\n");
        return (-1);
    }

    if(unlink(file_name) == (-1)) {
        printf("unlink returned (-1)\n");
        return (-1);
    }

    return 0;
}


