#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(int argc, char* argv[]) {
    char* hello_with_syscall = "Hello World with syscall\n";
    char* hello_without_syscall = "Hello World without syscall\n";
    char* hello_with_printf = "Hello World with printf\n";

    write( 1, hello_without_syscall, strlen( hello_without_syscall ));

    syscall( SYS_write, 1, hello_with_syscall, strlen( hello_with_syscall ));

    printf( "%s", hello_with_printf );

    return 0;
}


