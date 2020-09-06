#include "message.hh"
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    const char *sharedFileName = "shared.dat";
    const mode_t mode = 0666;
    const int openFlags = (O_CREAT | O_TRUNC | O_RDWR);
    int fd = open(sharedFileName, openFlags, mode);

    if(fd == (-1)) {
        printf("open returned (-1)\n");
        return (-1);
    }

    Message* msg = Message::CopyToMemoryMappedFile(fd);

    for(int i = 0; i < 100; i++) {
        char message[10];
        sprintf(message, "%d\n", i);
        msg->EnqueueMessage(&message[0]);
        printf("enqueued %d\n", i);
    }

    printf("message queue written\n");
    getchar();

    Message::ReleaseFile(msg, fd);

    close(fd);
}


