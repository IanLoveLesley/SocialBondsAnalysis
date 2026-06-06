//
// Created by Ian on 2026/6/3.
//

#ifndef SOCIALBONDSANALYSIS_PERSON_H
#define SOCIALBONDSANALYSIS_PERSON_H
#include "MyString.h"
#include "Sex.h"

class Person {
    int id;
    MyString name;
    Sex sex;
    int age;
    MyString job;
    public:
    Person();
    Person(int id,const char* name,Sex sex, int age,const char* job);
    int getId() const;
    Sex getSex() const;
    int getAge() const;
    const char* getName() const;
    const char* getJob() const;
    void printInfo() const;
};


#endif //SOCIALBONDSANALYSIS_PERSON_H