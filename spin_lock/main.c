#include "lock.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

long int count;
unsigned long lock = 0;

void *increment(void *vp_ntimes) {
    long ntimes = (long) vp_ntimes;
    for (long i = 0; i < ntimes; i++) {
        int c;
        //spin_lock(&lock);
        c = count;
        c = c + 1;
        count = c;
        //spin_unlock(&lock);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    const long int n = 100000000;

    pthread_t thread1, thread2;
    pthread_attr_t threadAttribute;

    pthread_attr_init(&threadAttribute);
    pthread_attr_setscope(&threadAttribute, PTHREAD_SCOPE_SYSTEM);

    printf("starting test. final count should be %ld\n", 2 * n);

    pthread_create(&thread1, &threadAttribute, increment, (void *) n);
    pthread_create(&thread2, &threadAttribute, increment, (void *) n);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    if (count != 2 * n) {
        printf("****** Error. Final count is %ld\n", count);
    } else {
        printf("****** OK. Final count is %ld\n", count);
    }

    return 1;
}


