#include "list.hh"
#include "debug.hh"

Node::Node(int value)
{
    assert(value != 0)
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

List::List()
{
    _tail = new Node((-1));
    _head = new Node((-1));
    _head->set_next(_tail);
    _head->set_prev(NULL);
    _tail->set_next(NULL);
    _tail->set_prev(_head);

    assert(_head->get_next() == _tail)
    assert(_tail->get_prev() == _head)
}

List::~List()
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

void List::add(int value)
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

int List::count()
{
    int count = 0;
    for(Node* curr = _head->get_next();
            curr != _tail;
            curr = curr->get_next())
    {
        assert(curr != NULL)
        count += 1;
    }
    return count;
}

Node* find(Node* head, int offset)
{
    Node* curr = head->get_next();
    for(int i = 0; i < offset; i++)
    {
        assert(curr != NULL)
        curr = curr->get_next();
    }
    return curr;
}

void List::remove(int index)
{
    Node* node = find(_head, index);
    assert(node != NULL)
    assert(node->get_prev() != NULL)
    assert(node->get_next() != NULL)
    node->get_prev()->set_next(node->get_next());
    node->get_next()->set_prev(node->get_prev());
    delete node;
}

int List::get(int index)
{
    Node* node = find(_head, index);
    assert(node != NULL)
    return node->get_value();
}
