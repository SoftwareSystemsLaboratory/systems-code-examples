#ifndef LIST_H
#define LIST_H

class Node {
public:
    Node(int value);
    ~Node();
    int get_value();
    Node* get_next();
    void set_next(Node *next);
    Node* get_prev();
    void set_prev(Node *prev);
private:
    Node* _next;
    Node* _prev;
    int _value;
};

class Queue {
public:
    Queue();
    ~Queue();
    void enqueue(int value);
    int dequeue();
    bool is_empty();
    bool has_work_left();
    void done_adding();
private:
    Node* _head;
    Node* _tail;
    bool _work_left;
};

#endif
