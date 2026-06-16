//
// Created by Ian on 2026/6/3.
//

#include "../include/MyString.h"
#include <iomanip>

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

MyString &MyString::operator=(const char* other)
{
    if (other == data)
    {
        return *this;
    }
    delete [] data;
    this->length = strlen(other);
    data = new char[length + 1];
    strcpy(data, other);
    return *this;
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
    int judge= true; // 先默认为true，只要遇到任何足以否定的依据就改为false
    if (length != other.length) {
        judge=false;
    }
    else {
        for (int i = 0; i < length; i++) {
            if (data[i] != other.data[i]) {
                judge=false;
                break;
            }
        }
    }
    return judge;
}

std::ostream& operator<<(std::ostream& out, const MyString& source)
{
    out << source.data;
    return out;
}

std::istream& operator>>(std::istream& in, MyString& target)
{
    char temp[1024];
    in >> std::setw(sizeof(temp)) >> temp; // 最多只读入1023个字符以及'\0'
    target = temp;
    return in;   
}