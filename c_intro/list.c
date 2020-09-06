#include "list.hh"
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

List::List() {
    _tail = new Node((-1));
    _head = new Node((-1));
    _head->setNext(_tail);
    _head->setPrev(NULL);
    _tail->setNext(NULL);
    _tail->setPrev(_head);

    assert(_head->getNext() == _tail)
    assert(_tail->getPrev() == _head)
}

List::~List() {
    for(Node* curr = _head->getNext(); curr != _tail; ) {
        Node* toDelete = curr;
        curr = curr->getNext();
        assert(curr != NULL)
        delete toDelete;
    }
    delete _tail;
    delete _head;
}

void List::Add(int x) {
    Node *prev = _tail->getPrev();
    Node *curr = new Node(x);
    assert(prev != NULL)
    assert(curr != NULL)
    curr->setNext(_tail);
    curr->setPrev(prev);
    prev->setNext(curr);
    _tail->setPrev(curr);
}

int List::Count() {
    int count = 0;
    for(Node* curr = _head->getNext();
            curr != _tail;
            curr = curr->getNext()) {
        assert(curr != NULL)
        count += 1;
    }
    return count;
}

Node* find(Node* head, int offset) {
    Node* curr = head->getNext();
    for(int i = 0; i < offset; i++) {
        assert(curr != NULL)
        curr = curr->getNext();
    }
    return curr;
}

void List::Remove(int index) {
    Node* node = find(_head, index);
    assert(node != NULL)
    assert(node->getPrev() != NULL)
    assert(node->getNext() != NULL)
    node->getPrev()->setNext(node->getNext());
    node->getNext()->setPrev(node->getPrev());
    delete node;
}

int List::Get(int index) {
    Node* node = find(_head, index);
    assert(node != NULL)
    return node->getValue();
}

