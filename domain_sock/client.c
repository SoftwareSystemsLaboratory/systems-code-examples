#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

int client_connect(const char* fileName) {
    int socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0) {
        printf("socket() failed\n");
        return (-1);
    }

    struct sockaddr_un address;
    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    sprintf(address.sun_path, fileName);

    if(connect(socket_fd, (struct sockaddr*)&address, sizeof(struct sockaddr_un)) != 0) {
        printf("connect() failed\n");
        return (-1);
    }

    char buffer[256];
    int nBytes = snprintf(buffer, 256, "hello from a client");
    write(socket_fd, buffer, nBytes);

    nBytes = read(socket_fd, buffer, 256);
    buffer[nBytes] = 0;

    printf("message from server: %s\n", buffer);

    close(socket_fd);

    return 0;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("usage:\n");
        printf("client [socket file]\n");
        return (-1);
    }
    return client_connect(argv[1]);
}
