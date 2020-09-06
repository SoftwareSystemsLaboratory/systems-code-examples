#ifndef MESSAGE_HH
#define MESSAGE_HH

#include <semaphore.h>

const int MessageQueueSize = (5);
const int MaxMessageSize = (20);

class Message {
public:
    ~Message();
    void EnqueueMessage(const char *msg);
    char* DequeueMessage();
    static Message *CopyToMemoryMappedFile(int fd);
    static Message *GetFromMemoryMappedFile(int fd);
    static void ReleaseFile(Message *msg, int fd);
private:
    Message();
    sem_t _lock;
    sem_t _empty;
    sem_t _full;
    int _current;
    char _messages[MessageQueueSize][MaxMessageSize];
};

#endif
