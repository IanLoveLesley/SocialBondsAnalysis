//
// Created by Ian on 2026/6/3.
//

#ifndef SOCIALBONDSANALYSIS_MYSTRING_H
#define SOCIALBONDSANALYSIS_MYSTRING_H
#include <cstring>
#include <iostream>

class MyString {
public:
    // 方便使用：可以直接利用operator<< 输出 MyString
    friend std::ostream& operator<<(std::ostream& out, const MyString& source);
    friend std::istream& operator>>(std::istream& in, MyString& target);
private:
    char *data;
    // 不包括末尾的'\0'
    int length;
    public:
    MyString();
    MyString(const char* str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data,str);
    }
    ~MyString() {
        delete[] data;
    }
    MyString(const MyString& other);
    MyString& operator=(const char* other);
    MyString& operator=(const MyString& other);
    bool operator==(const MyString& other)const;
    int getLength()const;
    const char* getData()const;
};


#endif //SOCIALBONDSANALYSIS_MYSTRING_H