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

class List {
public:
    List();
    ~List();
    void Add(int x);
    void Remove(int index);
    int Get(int index);
    int Count();
private:
    Node* _head;
    Node* _tail;
};

#endif

