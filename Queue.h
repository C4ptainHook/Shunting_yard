#pragma once
#include <iostream>
#include <stdexcept>
#include <memory>

template<class T>
class queue{
    struct Node {
        T data;
        std::shared_ptr<Node> next;
       explicit Node(T _data ): data(_data) {}
        ~Node() {
            next.reset();}
    };
    std::shared_ptr<Node> entrance;
    std::shared_ptr<Node>  exit;
    unsigned int size;
public:
    class iterator{
        Node* curr_ptr;
    public:
        iterator()=default;
        explicit iterator(Node* ptr): curr_ptr(ptr) {}
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
    queue(queue<T>&&) noexcept;
    void push(T);
    void pop();
    void clear();
    const T& back() const;
    const T& front() const;
    bool empty() const;
    queue<T>::iterator begin();
    queue<T>::iterator end();
    queue<T>& operator=(queue<T>&&) noexcept;
    queue<T>& operator=(queue<T>const &other);
};
//----------------------------------------------------------------Methods of queue
template<class T>
queue<T>::queue() {
    entrance = nullptr;
    exit = nullptr;
    size = 0;
}

template<class T>
queue<T>::queue(queue<T>&& other) noexcept{
    if (this->entrance)
        clear();
    this->entrance = other.entrance;
    this->exit = other.exit;
    this->size = other.size;
    other.entrance = nullptr;
    other.exit = nullptr;
    other.size = 0;
}


template<class T>
void queue<T>::push(T _data) {
    std::shared_ptr<Node> temp(new Node(_data));
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
        std::shared_ptr<Node> temp = entrance;
        entrance = temp->next;
        temp->next = nullptr;
        temp.reset();
        size--;
    }
}
template<class T>
queue<T>& queue<T>::operator=(queue<T>&& other) noexcept{
    if (this->entrance)
        clear();
    this->entrance = other.entrance;
    this->exit = other.exit;
    this->size = other.size;
    other.entrance = nullptr;
    other.exit = nullptr;
    other.size = 0;
return *this;
}

template<class T>
queue<T>& queue<T>::operator=(queue<T>const& other) {
entrance = nullptr;
exit = nullptr;
size = 0;
queue<T>::iterator it;
    for (it = other.begin(); it != other.end(); it++) {
        this->push(*it.curr_ptr->data);
    }
    return *this;
}

template<class T>
typename queue<T>::iterator queue<T>::begin() {
    return iterator(entrance.get());
}

template<class T>
typename queue<T>::iterator queue<T>::end() {
    return iterator(exit.get());
}

template<class T>
const T& queue<T>::back() const {
    return exit->data;
}

template<class T>
const T& queue<T>::front() const {
    return entrance->data;
}

template<class T>
bool queue<T>::empty() const {
    return !size;
}

template<class T>
void queue<T>::clear() {
    while(!this->empty())
        this->pop();
}
//--------------------------------------------------------------------------Methods of iterator

template<class T>
typename queue<T>::iterator& queue<T>::iterator::operator++() {
    this->curr_ptr=curr_ptr->next.get();
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
