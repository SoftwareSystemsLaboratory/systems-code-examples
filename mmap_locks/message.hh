#ifndef MESSAGE_HH
#define MESSAGE_HH

#include <semaphore.h>

const int message_queue_size = (5);
const int max_message_size = (20);

class Message {
public:
    ~Message();
    void enqueue_message(const char *msg);
    char* dequeue_message();
    static Message *copy_to_memory_mapped_file(int fd);
    static Message *get_from_memory_mapped_file(int fd);
    static void release_file(Message *msg, int fd);
private:
    Message();
    sem_t _lock;
    sem_t _empty;
    sem_t _full;
    int _current;
    char _messages[message_queue_size][max_message_size];
};

#endif
