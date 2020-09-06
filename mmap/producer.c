#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

int main(int argc, char* argv[]) {

    const char *data = "Hello World";
    int dataSize = sizeof(char) * strlen(data) + sizeof(char);

    const char *sharedFileName = "shared.dat";
    const mode_t mode = 0666;
    const int openFlags = (O_CREAT | O_TRUNC | O_RDWR);
    const int dummyValue = 0;
    int fd = open(sharedFileName, openFlags, mode);

    if(fd == (-1)) {
        printf("open returned (-1)\n");
        return (-1);
    }

    if(lseek(fd, dataSize, SEEK_SET) == (-1)) {
        printf("error in lseek\n");
        close(fd);
        return (-1);
    }
    if(write(fd, (char*)&dummyValue, sizeof(char)) == (-1)) {
        printf("error in write\n");
        close(fd);
        return (-1);
    }

    int protection = (PROT_READ | PROT_WRITE);
    int mapFlags   = MAP_SHARED;
    void* map = mmap(NULL, dataSize, protection, mapFlags, fd, 0);

    if(map == (void*)(-1)) {
        printf("mmap returned -1\n");
        close(fd);
        return (-1);
    }

    memcpy(map, data, dataSize);

    printf("memory mapped. press any key to exit...\n");
    getchar();

    if(munmap(map, dataSize) == (-1)) {
        printf("munmap returned -1\n");
        close(fd);
        return (-1);
    }

    close(fd);
}


