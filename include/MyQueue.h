//
// Created by 16507 on 2026/6/3.
//

#ifndef SOCIALBONDSANALYSIS_MYQUEUE_H
#define SOCIALBONDSANALYSIS_MYQUEUE_H

template <class T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode(T data) {
        this->data = data;
        this->next = NULL;
    }
};
template <class T>
class MyQueue {
    ListNode<T>* head;
    ListNode<T>* tail;
    int size;
    public:
    MyQueue() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    ~MyQueue() {
        while (head != nullptr) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
    void push(T data) {
        ListNode<T>* newNode = new ListNode<T>(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = tail->next;
        }
        size++;
    }
    void pop() {
        if (head == nullptr) {
            return;
        }
        else {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            if (head == nullptr) {
                tail = nullptr;
            }
        }
    }
    T& front() {
        return head->data;
    }
    const T& front() const {
        return head->data;
    }
    bool isEmpty() const {
        return head == nullptr;
    }
    int getSize() const {
        return size;
    }
};


#endif //SOCIALBONDSANALYSIS_MYQUEUE_H