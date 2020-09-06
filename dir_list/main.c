#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    const char *dir = "/";

    DIR *d = opendir(dir);

    struct dirent *de;
    while((de = readdir(d)) != NULL) {
        printf("name: %s\n", de->d_name);
    }

    closedir(d);
    return 0;
}


