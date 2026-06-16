//
// Created by Ian on 2026/6/3.
//

#pragma once
#include "../include/Person.h"
#include "../include/Sex.h"

Person::Person() {
    id = -1;
    // 应用enum class时需要注意，作用域外访问枚举值需要加上作用域限定符
    sex = Sex::FEMALE;
    age = 0;
}

Person::Person(int id, const char *name, Sex sex, int age, const char *job) {
    this->id = id;
    this->name = name;
    this->sex = sex;
    this->age = age;
    this->job = job;
}
Person::Person(int id,MyString name,Sex sex, int age, MyString job)
{
    this->id = id;
    this->name = name;
    this->sex = sex;
    this->age = age;
    this->job = job;
}

int Person::getAge() const {
    return age;
}
const char* Person::getName() const {
     return name.getData();
}
const char* Person::getJob() const {
    return job.getData();
}
int Person::getId() const {
    return id;
}

Sex Person::getSex() const {
    return sex;
}

void Person::printInfo() const {
    std::cout<<name<<std::endl;
    std::cout<<sex<<std::endl;
    std::cout<<age<<std::endl;
    std::cout<<job<<std::endl;
}

