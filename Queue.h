#pragma once
#include <iostream>
#include <stdexcept>

template<class T>
class queue{
    struct Node {
        T data;
        Node* next;
        Node(Node* _next, T _data ): next(_next), data(_data) {}
        ~Node() {
            delete next;}
    };
    Node* entrance;
    Node* exit;
    unsigned int size;
public:
    class iterator{
        Node* curr_ptr;
    public:
        iterator()=default;
        iterator(*Node);
        iterator& operator++();
        const iterator operator++(int);
        T operator*();
        T* operator->();
        bool operator==(const iterator&);
        bool operator!=(const iterator&);

        friend class queue<T>;
    };
public:
    queue();
    void push(T);
    void pop();
    queue<T>::iterator begin();
    queue<T>::iterator end();
};
//----------------------------------------------------------------Methods of queue
template<class T>
queue<T>::queue() {
    entrance = nullptr;
    exit = nullptr;
    size = 0;
}

template<class T>
void queue<T>::push(T _data) {
    Node* temp = new Node(nullptr, _data);
    if(!entrance)
        entrance=exit=temp;
    else{
        exit->next=temp;
        exit=temp;
    }
    size++;
}

template<class T>
void queue<T>::pop() {
    if(!entrance) {
        throw std::range_error("ERROR\nAttept to pop from empty queue!");
    }
    else{
        Node* temp = entrance;
        entrance = temp->next;
        temp->next = nullptr;
        delete temp;
        size--;
    }
}

template<class T>
typename queue<T>::iterator queue<T>::begin() {
    return iterator(entrance);
}

template<class T>
typename queue<T>::iterator queue<T>::end() {
    return iterator(exit);
}

//--------------------------------------------------------------------------Methods of iterator

template<class T>
typename queue<T>::iterator& queue<T>::iterator::operator++() {
    this->curr_ptr=curr_ptr->next;
    return *this;
}

template<class T>
const typename queue<T>::iterator queue<T>::iterator::operator++(int) {
    queue<T>::iterator temp(curr_ptr);
    ++(*this);
    return temp;
}

template<class T>
T queue<T>::iterator::operator*() {
    return curr_ptr->data;
}

template<class T>
T* queue<T>::iterator::operator->() {
    return &(curr_ptr->data);
}

template<class T>
bool queue<T>::iterator::operator==(const queue<T>::iterator& other) {
    return this->curr_ptr==other.curr_ptr;
}

template<class T>
bool queue<T>::iterator::operator!=(const queue<T>::iterator& other) {
    return this->curr_ptr!=other.curr_ptr;
}
