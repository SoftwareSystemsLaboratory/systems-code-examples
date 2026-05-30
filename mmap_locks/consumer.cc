#include "message.hh"
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

    const char *shared_file_name = "shared.dat";
    const mode_t mode = 0666;
    const int open_flags = (O_RDWR);
    int fd = open(shared_file_name, open_flags, mode);

    if(fd == (-1))
    {
        printf("open returned (-1)\n");
        return (-1);
    }

    Message* msg = Message::get_from_memory_mapped_file(fd);

    int count = 0;

    while(1)
    {
        char *message = msg->dequeue_message();
        printf("%d: %s", ++count, message);
        fflush(stdout);
    }

    Message::release_file(msg, fd);

    close(fd);
}

