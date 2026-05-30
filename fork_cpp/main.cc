#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string>

int main() {
    int some_value = 100;
    int pid = fork();
    int fd = open("test_file", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    std::string parent_message = "1111111";
    std::string child_message = "22222222222222\n";

    if (pid > 0) {
        std::cout << "hello from the parent process, child pid = " << pid << std::endl;
        sleep(2);
        std::cout << "parent's some_value = " << some_value << std::endl;

        write(fd, parent_message.c_str(), parent_message.length());

        wait(nullptr);
    } else if (pid == 0) {
        std::cout << "hello from the child process\n";
        some_value = 200;
        std::cout << "child's some_value = " << some_value << std::endl;

        write(fd, child_message.c_str(), child_message.length());
    } else {
        std::cout << "fork() failed!!" << std::endl;
    }

    close(fd);

    return 0;
}
