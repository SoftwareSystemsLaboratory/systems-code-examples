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

class List {
public:
    List();
    ~List();
    void add(int value);
    void remove(int index);
    int get(int index);
    int count();
private:
    Node* _head;
    Node* _tail;
};

#endif
