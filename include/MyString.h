//
// Created by Ian on 2026/6/3.
//

// 这个类可能会被废掉
#ifndef SOCIALBONDSANALYSIS_MYSTRING_H
#define SOCIALBONDSANALYSIS_MYSTRING_H
#include <cstring>


class MyString {
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
    MyString& operator=(const MyString& other);
    bool operator==(const MyString& other)const;
    int getLength()const;
    const char* getData()const;
};


#endif //SOCIALBONDSANALYSIS_MYSTRING_H