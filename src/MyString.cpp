//
// Created by Ian on 2026/6/3.
//

#include "../include/MyString.h"

MyString::MyString() {
    length = 0;
    data = new char[1];
    data[0] = '\0';
}

MyString::MyString(const MyString &other) {
    this->length = other.length;
    this->data = new char[length + 1];
    strcpy(this->data, other.data);
}

MyString &MyString::operator=(const MyString &other) {
    if (this == &other) {
        return *this;
    }
    else {
        delete [] data;
        this->length = other.length;
        this->data = new char[length + 1];
        strcpy(this->data, other.data);
        return *this;
    }

}

int MyString::getLength() const {
    return length;
}
const char* MyString::getData() const {
    return data;
}

bool MyString::operator==(const MyString& other) const{
    int judge=1;
    if (length != other.length) {
        judge=0;
    }
    else {
        for (int i = 0; i < length; i++) {
            if (data[i] != other.data[i]) {
                judge=0;
                break;
            }
        }
    }
    return judge;
}
