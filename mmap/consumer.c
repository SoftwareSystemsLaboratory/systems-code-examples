#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

int get_file_size(const char *file_name) {
    struct stat file_stat;
    stat(file_name, &file_stat);
    return file_stat.st_size;
}

int main(int argc, char *argv[]) {

    const mode_t mode = 0666;
    const int open_flag = (O_RDWR);
    const char *file_name = "shared.dat";
    int file_size = get_file_size(file_name);

    int fd = open(file_name, open_flag, mode);
    if (fd == (-1)) {
        printf("error in open\n");
        return (-1);
    }

    int protection = (PROT_READ | PROT_WRITE);
    int map_flags = MAP_SHARED;
    void *map = mmap(NULL, file_size, protection, map_flags, fd, 0);

    if (map == (void *) (-1)) {
        printf("mmap() returned -1\n");
        close(fd);
    }

    char *data = (char *) calloc(1, file_size);

    memcpy(data, map, file_size);

    printf("%s\n", data);

    free(data);

    if (munmap(map, file_size) == (-1)) {
        printf("munmap() failed\n");
        close(fd);
        return (-1);
    }

    close(fd);

    return 0;
}
