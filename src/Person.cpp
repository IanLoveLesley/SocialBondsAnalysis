//
// Created by Ian on 2026/6/3.
//

#include "../include/Person.h"
#include <iostream>

Person::Person() {
    id = -1;
    sex = 0;
    age = 0;
}

Person::Person(int id, const char *name, int sex, int age, const char *job) {
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

int Person::getSex() const {
    return sex;
}

void Person::printInfo() const {
    std::cout<<name.getData()<<std::endl;
    std::cout<<sex<<std::endl;
    std::cout<<age<<std::endl;
    std::cout<<job.getData()<<std::endl;
}
