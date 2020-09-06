#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

int getFileSize(const char *fileName) {
    struct stat fileStat;
    stat(fileName, &fileStat);
    return fileStat.st_size;
}

int main(int argc, char* argv[]) {

    const mode_t mode = 0666;
    const int openFlag = (O_RDWR);
    const char *fileName = "shared.dat";
    int fileSize = getFileSize(fileName);

    int fd = open(fileName, openFlag, mode);
    if(fd == (-1)) {
        printf("error in open\n");
        return (-1);
    }

    int protection = (PROT_READ | PROT_WRITE);
    int mapFlags = MAP_SHARED;
    void* map = mmap(NULL, fileSize, protection, mapFlags, fd, 0);

    if(map == (void*)(-1)) {
        printf("mmap() returned -1\n");
        close(fd);
    }

    char *data = (char*)calloc(1, fileSize);

    memcpy(data, map, fileSize);

    printf("%s\n", data);

    free(data);

    if(munmap(map, fileSize) == (-1)) {
        printf("munmap() failed\n");
        close(fd);
        return (-1);
    }

    close(fd);

    return 0;
}

