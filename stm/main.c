#include "trans.hh"
#include <pthread.h>
#include <stdio.h>

const int countPerThread = 10000000;
volatile int count = 0;
Transaction *trans = new Transaction(&count);

void increment() {
    const int chunkSize = 500;
    for(int i = 0; i < countPerThread; i += chunkSize) {
        MemHandle* handle;
        do {
            handle = trans->Begin();
            for(int j = 0; j < chunkSize; j++) {
                handle->Value += 1;
            }
        } while(!trans->TryCommit(handle));
    }
}

int main( int argc, char* argv[]) {

    pthread_t thread1, thread2;
    pthread_attr_t threadAttribute;

    pthread_attr_init(&threadAttribute);
    pthread_attr_setscope(&threadAttribute, PTHREAD_SCOPE_SYSTEM);

    printf("starting test. final count should be %d\n", 2*countPerThread);

    pthread_create(&thread1, &threadAttribute, (void * (*)(void*))increment, (void*)NULL);
    pthread_create(&thread2, &threadAttribute, (void * (*)(void*))increment, (void*)NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    if( count != 2 * countPerThread ) {
        printf("****** Error. Final count is %d\n", count);
    } else {
        printf("****** OK. Final count is %d\n", count);
    }

    printf("rollback count = %d\n", trans->GetRollbackCount());

    return 1;
}


