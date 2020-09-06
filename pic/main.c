#include <unistd.h>

const char *msg = "abcdefg";

int main(int argc, char* argv[]) {

    const char *x = msg + 1;

    write(1, x, 1);

    return (0);

}

