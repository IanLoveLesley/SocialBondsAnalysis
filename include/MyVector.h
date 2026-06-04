//
// Created by Ian on 2026/6/3.
//

#ifndef SOCIALBONDSANALYSIS_MYVECTOR_H
#define SOCIALBONDSANALYSIS_MYVECTOR_H

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
    ~MyVector() {
        delete[] data;
    }
    int getSize()const {
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
};


#endif //SOCIALBONDSANALYSIS_MYVECTOR_H