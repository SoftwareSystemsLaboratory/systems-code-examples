#include "message.hh"
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

    const char *shared_file_name = "shared.dat";
    const mode_t mode = 0666;
    const int open_flags = (O_CREAT | O_TRUNC | O_RDWR);
    int fd = open(shared_file_name, open_flags, mode);

    if(fd == (-1))
    {
        printf("open returned (-1)\n");
        return (-1);
    }

    Message* msg = Message::copy_to_memory_mapped_file(fd);

    for(int i = 0; i < 100; i++)
    {
        char message[10];
        sprintf(message, "%d\n", i);
        msg->enqueue_message(&message[0]);
        printf("enqueued %d\n", i);
    }

    printf("message queue written\n");
    getchar();

    Message::release_file(msg, fd);

    close(fd);
}

