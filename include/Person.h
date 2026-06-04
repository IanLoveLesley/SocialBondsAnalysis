//
// Created by Ian on 2026/6/3.
//

#ifndef SOCIALBONDSANALYSIS_PERSON_H
#define SOCIALBONDSANALYSIS_PERSON_H
#include "MyString.h"

class Person {
    int id;
    MyString name;
    int sex;
    int age;
    MyString job;
    public:
    Person();
    Person(int id,const char* name,int sex, int age,const char* job);
    int getId() const;
    int getSex() const;
    int getAge() const;
    const char* getName() const;
    const char* getJob() const;
    void printInfo() const;
};


#endif //SOCIALBONDSANALYSIS_PERSON_H