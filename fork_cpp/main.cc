#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string>

int main() {
    int SomeValue = 100;
    int pid = fork();
    int fd = open("test_file", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    // Converting to std::string
    std::string parentMessage = "1111111";
    std::string childMessage = "22222222222222\n";

    if (pid > 0) {
        // Parent process
        std::cout << "hello from the parent process, child pid = " << pid << std::endl;
        sleep(2);
        std::cout << "parent's SomeValue = " << SomeValue << std::endl;

        // Using write() here because we're working with file descriptors directly
        write(fd, parentMessage.c_str(), parentMessage.length());

        // Wait for child process to prevent a zombie process
        wait(nullptr);
    } else if (pid == 0) {
        // Child process
        std::cout << "hello from the child process\n";
        SomeValue = 200;
        std::cout << "child's SomeValue = " << SomeValue << std::endl;

        write(fd, childMessage.c_str(), childMessage.length());
    } else {
        std::cout << "fork() failed!!" << std::endl;
    }

    close(fd);

    return 0;
}
