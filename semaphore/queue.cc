#include "queue.hh"
#include "debug.hh"

Node::Node(int value) {
    assert(value != NULL)
    _value = value;
}

Node::~Node() {
}

int Node::getValue() {
    return this->_value;
}

Node* Node::getNext() {
    return this->_next;
}

void Node::setNext(Node *next) {
    this->_next = next;
}

Node* Node::getPrev() {
    return this->_prev;
}

void Node::setPrev(Node* prev) {
    this->_prev = prev;
}

Queue::Queue() {
    _tail = new Node((-1));
    _head = new Node((-1));
    _head->setNext(_tail);
    _head->setPrev(NULL);
    _tail->setNext(NULL);
    _tail->setPrev(_head);
    _workLeft = true;

    assert(_head->getNext() == _tail)
    assert(_tail->getPrev() == _head)
}

Queue::~Queue() {
    for(Node* curr = _head->getNext(); curr != _tail; ) {
        Node* toDelete = curr;
        curr = curr->getNext();
        assert(curr != NULL)
        delete toDelete;
    }
    delete _tail;
    delete _head;
}

void Queue::Enqueue(int x) {
    Node *prev = _tail->getPrev();
    Node *curr = new Node(x);
    assert(prev != NULL)
    assert(curr != NULL)
    curr->setNext(_tail);
    curr->setPrev(prev);
    prev->setNext(curr);
    _tail->setPrev(curr);
}

int Queue::Dequeue() {
    Node* node = _head->getNext();
    node->getPrev()->setNext(node->getNext());
    node->getNext()->setPrev(node->getPrev());
    int value = node->getValue();
    delete node;
    return value;
}

bool Queue::HasWorkLeft() {
    return _head->getNext() != _tail || _workLeft;
}

void Queue::DoneAdding() {
    _workLeft = false;
}



