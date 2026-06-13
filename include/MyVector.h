//
// Created by Ian on 2026/6/3.
//

#ifndef SOCIALBONDSANALYSIS_MYVECTOR_H
#define SOCIALBONDSANALYSIS_MYVECTOR_H

#include <algorithm> // 需要 std::fill_n

template <class T>
class MyVector {
    T *data;
    int capacity;
    int size;
    
    public:
    MyVector() {
        size = 0;
        capacity = 256;
        data = new T[capacity];
    }
    MyVector(int size, T original_value)
    {
        this->size = this->capacity = size;
        data = new T[capacity];
        // 将每一处数据都设置为 original_value
        std::fill_n(data, size, original_value);
    }
    ~MyVector() {
        delete[] data;
    }

    inline int getSize()const {
        return size;
    }

    T& operator[](int index) {
        return data[index];
    }
    const T& operator[](int index) const {
        return data[index];
    }

    void push_back(const T& item) {
        if (size == capacity) {
            capacity *= 2;
            T* newData = new T[capacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size] = item;
        size++;
    }

    MyVector(const MyVector& other) {
        this->size = other.size;
        this->capacity = other.capacity;

        this->data = new T[this->capacity];

        for (int i = 0; i < this->size; i++) {
            this->data[i] = other.data[i];
        }
    }

    MyVector& operator=(const MyVector& other) {
        if (this == &other) {
            return *this;
        }

        delete[] this->data;
        this->size = other.size;
        this->capacity = other.capacity;
        this->data = new T[this->capacity];
        for (int i = 0; i < this->size; i++) {
            this->data[i] = other.data[i];
        }

        return *this;
    }

    bool has(T target)
    {
        for (int i = 0; i < size; i++)
        {
            if (data[i] == target)
            {
                return true;
            }
        }
        return false;
    }

    inline void clear(){size = 0;} // 只需一步；彻底放弃垃圾数据

    void add(MyVector<T> &source)
    {
        for (int i = 0; i < source.getSize(); i++)
        {
            push_back(source[i]);
        }
    }
};


#endif //SOCIALBONDSANALYSIS_MYVECTOR_H