#ifndef SHUNTING_YARD_STACK_H
#define SHUNTING_YARD_STACK_H
#pragma once
#include <iostream>
#include <stdexcept>
#include <fstream>

template<class T>
class stack {
    struct Node {
        T data;
        Node* next;
        Node(Node* _next, T _data ): next(_next), data(_data) {}
        ~Node() {
            delete next;}
    };
    Node* top;
    unsigned int size;
public:
    stack();
    void push(T);
    void pop();
    void clear();
    bool empty();
};

template<class T>
stack<T>::stack() {
    top = nullptr;
    size = 0;
}

template<class T>
void stack<T>::push(T _data) {
    if(top==nullptr) {
        Node* temp = new Node(nullptr, _data);
        top=temp;
    }
    else{
    Node* temp = new Node(top, _data);
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


#endif //SHUNTING_YARD_STACK_H
