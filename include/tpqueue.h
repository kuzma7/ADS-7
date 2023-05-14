// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 private:
    struct Item {
        T data;
        Item* next;
        Item* pred;
    };
    Item* head;
    Item* tail;
    TPQueue::Item* create(const T&);

 public:
    TPQueue() : head(nullptr), tail(nullptr) { }
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
};

template <typename T>
typename TPQueue<T>::Item* TPQueue<T>::create(const T& data) {
    Item* item = new Item;
    item->data = data;
    item->next = nullptr;
    item->pred = nullptr;
    return item;
}

template <typename T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template <typename T>
void TPQueue<T>::push(const T& e) {
    if (head == nullptr) {
        head = create(e);
        tail = head;
    } else if (tail->data.prior >= e.prior) {
        if (tail->data.ch == e.ch) {
            tail->data = e;
        } else {
            tail->next = create(e);
            tail->next->pred = tail;
            tail = tail->next;
        }
    } else if (head == tail) {
        tail->pred = create(e);
        head = tail->pred;
        head->next = tail;
    } else {
        Item* tmp = tail;
        while (tmp != head && tmp->data.prior < e.prior) {
            tmp = tmp->pred;
        }
        if (tmp->data.prior > e.prior) {
            Item* cell = new Item;
            cell->next = tmp->next;
            cell->pred = tmp;
            cell->data = e;
            tmp->next->pred = cell;
            tmp->next = cell;
        }
        if (tmp == head && tmp->data.prior < e.prior) {
            head->pred = create(e);
            head = head->pred;
            head->next = tmp;
        }
    }
}

template <typename T>
T TPQueue<T>::pop() {
    if (!head) {
        throw std::string("Is Empty!");
    } else {
        Item* temp = head->next;
        T data = head->data;
        delete head;
        head = temp;
        return data;
    }
}

template <typename T>
void TPQueue<T>::print() const {
    Item* temp = head;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
