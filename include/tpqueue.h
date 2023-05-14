// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>
#include <iostream>
template<typename T>
class TPQueue {
private:
    struct Element {
        T data;
        Element* next;
        Element* last;
    };
    Element* head;
    Element* tail;
    TPQueue::Element* create(const T&);

public:
    TPQueue() : head(nullptr), tail(nullptr) { }
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
};

struct SYM {
  char ch;
  int prior;
};

template <typename T>
typename TPQueue<T>::Element* TPQueue<T>::create(const T& data) {
    Element* Element = new Element;
    Element->data = data;
    Element->next = nullptr;
    Element->last = nullptr;
    return Element;
}

template <typename T>
T TPQueue<T>::pop() {
    if (!head) {
        throw std::string("Oh, TPQueue is empty!");
    }
    else {
        Element* temp = head->next;
        T data = head->data;
        delete head;
        head = temp;
        return data;
    }
}

template <typename T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template <typename T>
void TPQueue<T>::print() const {
    Element* poi = head;
    while (poi) {
        std::cout << poi->data << " ";
        poi = poi->next;
    }
    std::cout << std::endl;
}

template <typename T>
void TPQueue<T>::push(const T& value) {
    if (head == nullptr) {
        head = create(value);
        tail = head;
    }
    else if (tail->data.prior >= value.prior) {
        if (tail->data.ch == value.ch) {
            tail->data = value;
        }
        else {
            tail->next = create(value);
            tail->next->last = tail;
            tail = tail->next;
        }
    }
    else if (head == tail) {
        tail->last = create(value);
        head = tail->last;
        head->next = tail;
    }
    else {
        Element* template = tail;
        while (template != head && template->data.prior < value.prior) {
            template = template->last;
        }
        if (template->data.prior > value.prior) {
            Element* cell = new Element;
            cell->next = template->next;
            cell->last = template;
            cell->data = value;
            template->next->last = cell;
            template->next = cell;
        }
        if (template == head && template->data.prior < value.prior) {
            head->last = create(value);
            head = head->last;
            head->next = template;
        }
    }
}

#endif  // INCLUDE_TPQUEUE_H_
