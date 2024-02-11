#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *data = "foobar";
    int fd = open("file", O_CREAT | O_TRUNC | O_RDWR, 0666);
    size_t length = strlen(data), offset = 0;
    while (length > 0) {
        size_t written = write(fd, data + offset, length);
        offset += written;
        length -= written;
    }
    close(fd);
}
