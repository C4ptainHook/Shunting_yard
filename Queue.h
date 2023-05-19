#ifndef SHUNTING_YARD_QUEUE_H
#define SHUNTING_YARD_QUEUE_H
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
    queue();
    void push(T);
    void pop();
};

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






#endif //SHUNTING_YARD_QUEUE_H
