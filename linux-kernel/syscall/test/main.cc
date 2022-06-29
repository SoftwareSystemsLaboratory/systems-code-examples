#include <unistd.h>
#include <stdio.h>

#define __NR_addsyscall (303)

long addsyscall(int x, int y)
{
    return syscall(__NR_addsyscall, x, y);
}

int main(int argc, char* argv[])
{
    int result = (int)addsyscall(2, 3);
    printf("result = %d\n", result);
    if(result == (-1))
    {
        perror("error");
    }
    return 0;
}
