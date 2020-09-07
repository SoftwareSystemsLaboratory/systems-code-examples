#include "message.hh"
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#define SEMA_TYPE (1)
#define SEMA_MUTEX (1)
#define SEMA_EVENT (0)

Message::Message() {
    sem_init(&_lock,  SEMA_TYPE, 1);
    sem_init(&_empty, SEMA_TYPE, 0);
    sem_init(&_full,  SEMA_TYPE, MessageQueueSize);
    _current = 0;
}

Message::~Message() {
}

Message *Message::CopyToMemoryMappedFile(int fd) {
    int datasize = sizeof(Message);
    printf("message size = %d\n", datasize);
    if(lseek(fd, sizeof(Message), SEEK_SET) == (-1)) {
        fprintf(stderr, "error in lseek\n");
    }
    int dummyVal = 0;
    if(write(fd, (char*)&dummyVal, sizeof(char)) == (-1)) {
        fprintf(stderr, "error in write\n");
    }
    void *map = mmap(NULL, sizeof(Message), (PROT_READ|PROT_WRITE), MAP_SHARED, fd, 0);
    if(map == (void*)(-1)) {
        fprintf(stderr, "mmap() returned -1\n");
    }
    Message *msg = new Message();
    memcpy(map, (void*)msg, sizeof(Message));
    delete msg;
    return (Message*)map;
}

Message *Message::GetFromMemoryMappedFile(int fd) {
    void *map = mmap(NULL, sizeof(Message), (PROT_READ|PROT_WRITE), MAP_SHARED, fd, 0);
    if(map == (void*)(-1)) {
        fprintf(stderr, "mmap() returned -1\n");
    }
    Message* msg = (Message*)map;
    return msg;
}

void Message::ReleaseFile(Message *msg, int fd) {
    if(munmap((void*)msg, sizeof(Message)) == (-1)) {
        fprintf(stderr, "munmap() failed\n");
    }
}

void Message::EnqueueMessage(const char *msg) {
    sem_wait(&_full);
    sem_wait(&_lock);
    _current += 1;
    bzero(&_messages[_current], MaxMessageSize*sizeof(char));
    memcpy(&_messages[_current], msg, strlen(msg)*sizeof(char));
    sem_post(&_lock);
    sem_post(&_empty);
}

char* Message::DequeueMessage() {
    char *msg = new char[MaxMessageSize];
    sem_wait(&_empty);
    sem_wait(&_lock);
    memcpy(msg, &_messages[_current], MaxMessageSize*sizeof(char));
    _current -= 1;
    sem_post(&_lock);
    sem_post(&_full);
    return msg;
}

