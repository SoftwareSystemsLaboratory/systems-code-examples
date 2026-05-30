#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

int main(int argc, char *argv[]) {

    const char *data = "Hello World";
    int data_size = sizeof(char) * strlen(data) + sizeof(char);

    const char *shared_file_name = "shared.dat";
    const mode_t mode = 0666;
    const int open_flags = (O_CREAT | O_TRUNC | O_RDWR);
    const int dummy_value = 0;
    int fd = open(shared_file_name, open_flags, mode);

    if (fd == (-1)) {
        printf("open returned (-1)\n");
        return (-1);
    }

    if (lseek(fd, data_size, SEEK_SET) == (-1)) {
        printf("error in lseek\n");
        close(fd);
        return (-1);
    }
    if (write(fd, (char *) &dummy_value, sizeof(char)) == (-1)) {
        printf("error in write\n");
        close(fd);
        return (-1);
    }

    int protection = (PROT_READ | PROT_WRITE);
    int map_flags = MAP_SHARED;
    void *map = mmap(NULL, data_size, protection, map_flags, fd, 0);

    if (map == (void *) (-1)) {
        printf("mmap returned -1\n");
        close(fd);
        return (-1);
    }

    memcpy(map, data, data_size);

    printf("memory mapped. press any key to exit...\n");
    getchar();

    if (munmap(map, data_size) == (-1)) {
        printf("munmap returned -1\n");
        close(fd);
        return (-1);
    }

    close(fd);
}

