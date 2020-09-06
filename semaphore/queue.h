#ifndef LIST_H
#define LIST_H

class Node {
public:
    Node(int value);
    ~Node();
    int getValue();
    Node* getNext();
    void setNext(Node *next);
    Node* getPrev();
    void setPrev(Node *prev);
private:
    Node* _next;
    Node* _prev;
    int _value;
};

class Queue {
public:
    Queue();
    ~Queue();
    void Enqueue(int val);
    int Dequeue();
    bool HasWorkLeft();
    void DoneAdding();
private:
    Node* _head;
    Node* _tail;
    bool _workLeft;
};

#endif

