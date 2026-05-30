#include "lock.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

long int count;
unsigned long lock = 0;

void *increment(void *vp_iterations) {
    long iterations = (long) vp_iterations;
    for (long i = 0; i < iterations; i++) {
        int local_count;
        //spin_lock(&lock);
        local_count = count;
        local_count = local_count + 1;
        count = local_count;
        //spin_unlock(&lock);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    const long int iterations = 100000000;

    pthread_t thread1, thread2;
    pthread_attr_t thread_attribute;

    pthread_attr_init(&thread_attribute);
    pthread_attr_setscope(&thread_attribute, PTHREAD_SCOPE_SYSTEM);

    printf("starting test. final count should be %ld\n", 2 * iterations);

    pthread_create(&thread1, &thread_attribute, increment, (void *) iterations);
    pthread_create(&thread2, &thread_attribute, increment, (void *) iterations);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    if (count != 2 * iterations) {
        printf("****** Error. Final count is %ld\n", count);
    } else {
        printf("****** OK. Final count is %ld\n", count);
    }

    return 1;
}
