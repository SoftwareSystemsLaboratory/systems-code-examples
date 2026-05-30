
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int connection_handler(int socket_fd) {
    char buffer[256];
    int byte_count = read(socket_fd, buffer, 256);
    buffer[byte_count] = 0;
    printf("message from client: %s\n", buffer);
    byte_count = snprintf(buffer, 256, "hello from server");
    write(socket_fd, buffer, byte_count);

    close(socket_fd);
    return 0;
}

int server_listen(const char *file_name) {
    int socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if (socket_fd == (-1)) {
        printf("socket() failed\n");
        return (-1);
    }

    unlink(file_name);

    struct sockaddr_un address;
    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    sprintf(address.sun_path, file_name);

    if (bind(socket_fd, (struct sockaddr *) &address, sizeof(struct sockaddr_un)) != 0) {
        printf("bind() failed\n");
        return (-1);
    }
    if (listen(socket_fd, 5) != 0) {
        printf("listen() failed\n");
        return (-1);
    }

    int connection_fd;
    socklen_t address_length;
    while ((connection_fd = accept(socket_fd, (struct sockaddr *) &address, &address_length)) > (-1)) {
        int child = fork();
        if (child == 0) {
            return connection_handler(connection_fd);
        } else {
            close(connection_fd);
        }
    }

    close(socket_fd);
    unlink(file_name);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage:");
        printf("server [socket file]\n");
        return (-1);
    }
    return server_listen(argv[1]);
}
