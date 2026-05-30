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

Message::Message()
{
    sem_init(&_lock,  SEMA_TYPE, 1);
    sem_init(&_empty, SEMA_TYPE, 0);
    sem_init(&_full,  SEMA_TYPE, message_queue_size);
    _current = 0;
}

Message::~Message()
{
}

Message *Message::copy_to_memory_mapped_file(int fd)
{
    int data_size = sizeof(Message);
    printf("message size = %d\n", data_size);
    if(lseek(fd, sizeof(Message), SEEK_SET) == (-1))
    {
        fprintf(stderr, "error in lseek\n");
    }
    int dummy_val = 0;
    if(write(fd, (char*)&dummy_val, sizeof(char)) == (-1))
    {
        fprintf(stderr, "error in write\n");
    }
    void *map = mmap(NULL, sizeof(Message), (PROT_READ|PROT_WRITE), MAP_SHARED, fd, 0);
    if(map == (void*)(-1))
    {
        fprintf(stderr, "mmap() returned -1\n");
    }
    Message *msg = new Message();
    memcpy(map, (void*)msg, sizeof(Message));
    delete msg;
    return (Message*)map;
}

Message *Message::get_from_memory_mapped_file(int fd)
{
    void *map = mmap(NULL, sizeof(Message), (PROT_READ|PROT_WRITE), MAP_SHARED, fd, 0);
    if(map == (void*)(-1))
    {
        fprintf(stderr, "mmap() returned -1\n");
    }
    Message* msg = (Message*)map;
    return msg;
}

void Message::release_file(Message *msg, int fd)
{
    if(munmap((void*)msg, sizeof(Message)) == (-1))
    {
        fprintf(stderr, "munmap() failed\n");
    }
}

void Message::enqueue_message(const char *msg)
{
    sem_wait(&_full);
    sem_wait(&_lock);
    _current += 1;
    bzero(&_messages[_current], max_message_size*sizeof(char));
    memcpy(&_messages[_current], msg, strlen(msg)*sizeof(char));
    sem_post(&_lock);
    sem_post(&_empty);
}

char* Message::dequeue_message()
{
    char *msg = new char[max_message_size];
    sem_wait(&_empty);
    sem_wait(&_lock);
    memcpy(msg, &_messages[_current], max_message_size*sizeof(char));
    _current -= 1;
    sem_post(&_lock);
    sem_post(&_full);
    return msg;
}
