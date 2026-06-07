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
        this->next = nullptr;
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
        // while (head != nullptr) {
        //     ListNode<T>* temp = head;
        //     head = head->next;
        //     delete temp;
        // }
        // temp变量只进行一次初始化，减少时间和空间开销
        for (ListNode<T>* temp = head; head != nullptr; )
        {
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
    // 取出队头数据和弹走队头数据分为两个步骤，这个是取出队头数据
    // 调用时需要指明是否为 const
    inline T& front() {
        return head->data;
    }
    inline const T& front() const {
        return head->data;
    }
    inline bool isEmpty() const {
        return head == nullptr;
    }
    inline int getSize() const {
        return size;
    }
};


#endif //SOCIALBONDSANALYSIS_MYQUEUE_H