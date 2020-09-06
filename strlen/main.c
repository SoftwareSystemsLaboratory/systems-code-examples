#include <stdio.h>

int my_strlen(const char *str) {
    int length = 0;
    while(*str != 0) {
        str++;
        length++;
    }
    return length;
}


int main(int argc, char* argv[]) {

    const char *str = "hello world";

    int len = my_strlen(str);

    printf("%d\n", len);

    return 0;
}
