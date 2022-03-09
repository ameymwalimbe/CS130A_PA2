#ifndef PERSON_H
#define PERSON_H

#include <vector>
#include <iostream>
using namespace std;

class Person{
    public:
        Person();
        Person(string line, int i); //constructs a person vertex and fills in their hobby vector
        void printVec();
    //private:   
        vector<float> hobbies;
        int number;
        
};

#endif