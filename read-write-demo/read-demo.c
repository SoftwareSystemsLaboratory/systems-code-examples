#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int fd = open("file", O_RDONLY, 0666);
    size_t length;
    char buffer[5];
    while ((length = read(fd, &buffer[0], 5)) != 0) {
        write(1, &buffer[0], length);
    }
    close(fd);

}
