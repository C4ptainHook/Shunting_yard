#pragma once
#include <iostream>
#include <stdexcept>

template<class T>
class stack {
    struct Node {
        T data;
        Node* next;
        explicit Node(T _data): data(_data) {}
        ~Node() {
            delete next;}
    };
    Node* top;
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

        friend class stack<T>;
    };
    stack();
    void push(T);
    void pop();
    void clear();
    bool empty();
    stack<T>::iterator begin();
    stack<T>::iterator end();
};
//----------------------------------------------------------------Methods of stack
template<class T>
stack<T>::stack() {
    top = nullptr;
    size = 0;
}

template<class T>
void stack<T>::push(T _data) {
    if(top==nullptr) {
        Node* temp = new Node(_data);
        top=temp;
    }
    else{
    Node* temp = new Node(_data);
    temp->next=top;
    top=temp;
    }
    size++;
}

template<class T>
void stack<T>::pop() {
    if(top==nullptr)
        throw std::range_error("Attempt to pop from empty stack!");
    Node* temp = top;
    top=temp->next;
    temp->next=nullptr;
    delete temp;
    size--;
}

template<class T>
void stack<T>::clear() {
    while(top) {
        pop();
    }
    size = 0;
}

template<class T>
bool stack<T>::empty() {
    if(!top)
        return true;
    return false;
}

template<class T>
typename stack<T>::iterator stack<T>::begin() {
    return iterator(this->top);
}

template<class T>
typename stack<T>::iterator stack<T>::end() {
    return iterator(nullptr);
}
//--------------------------------------------------------------------------Methods of iterator

template<class T>
typename stack<T>::iterator& stack<T>::iterator::operator++() {
    this->curr_ptr=curr_ptr->next;
    return *this;
}

template<class T>
const typename stack<T>::iterator stack<T>::iterator::operator++(int) {
    stack<T>::iterator temp(curr_ptr);
    ++(*this);
    return temp;
}

template<class T>
T stack<T>::iterator::operator*() {
    return curr_ptr->data;
}

template<class T>
T* stack<T>::iterator::operator->() {
    return &(curr_ptr->data);
}

template<class T>
bool stack<T>::iterator::operator==(const stack<T>::iterator& other) {
   return this->curr_ptr==other.curr_ptr;
}

template<class T>
bool stack<T>::iterator::operator!=(const stack<T>::iterator& other) {
    return this->curr_ptr!=other.curr_ptr;
}
