#include "queue.hh"
#include "debug.hh"

Node::Node(int value)
{
    _value = value;
}

Node::~Node()
{
}

int Node::get_value()
{
    return this->_value;
}

Node* Node::get_next()
{
    return this->_next;
}

void Node::set_next(Node *next)
{
    this->_next = next;
}

Node* Node::get_prev()
{
    return this->_prev;
}

void Node::set_prev(Node* prev)
{
    this->_prev = prev;
}

Queue::Queue()
{
    _tail = new Node((-1));
    _head = new Node((-1));
    _head->set_next(_tail);
    _head->set_prev(NULL);
    _tail->set_next(NULL);
    _tail->set_prev(_head);
    _work_left = true;

    assert(_head->get_next() == _tail)
    assert(_tail->get_prev() == _head)
}

Queue::~Queue()
{
    for(Node* curr = _head->get_next(); curr != _tail; )
    {
        Node* to_delete = curr;
        curr = curr->get_next();
        assert(curr != NULL)
        delete to_delete;
    }
    delete _tail;
    delete _head;
}

void Queue::enqueue(int value)
{
    Node *prev = _tail->get_prev();
    Node *curr = new Node(value);
    assert(prev != NULL)
    assert(curr != NULL)
    curr->set_next(_tail);
    curr->set_prev(prev);
    prev->set_next(curr);
    _tail->set_prev(curr);
}

int Queue::dequeue()
{
    Node* node = _head->get_next();
    node->get_prev()->set_next(node->get_next());
    node->get_next()->set_prev(node->get_prev());
    int value = node->get_value();
    delete node;
    return value;
}

bool Queue::has_work_left()
{
    return _head->get_next() != _tail || _work_left;
}

void Queue::done_adding()
{
    _work_left = false;
}

