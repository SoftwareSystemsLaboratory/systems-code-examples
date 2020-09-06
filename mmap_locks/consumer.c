#include "message.hh"
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    const char *sharedFileName = "shared.dat";
    const mode_t mode = 0666;
    const int openFlags = (O_RDWR);
    int fd = open(sharedFileName, openFlags, mode);

    if(fd == (-1)) {
        printf("open returned (-1)\n");
        return (-1);
    }

    Message* msg = Message::GetFromMemoryMappedFile(fd);

    int count = 0;

    while(1) {
        char *message = msg->DequeueMessage();
        printf("%d: %s", ++count, message);
        fflush(stdout);
    }

    Message::ReleaseFile(msg, fd);

    close(fd);
}


