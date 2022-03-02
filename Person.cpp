#include <string>
#include <sstream>
#include "Person.hpp"

Person::Person(string line) {
    stringstream ss (line);
    float f;
    while(ss>>f){
        if (ss.peek() == ','){
            ss.ignore();
        }
        hobbies.push_back(f);
    }

    // string temp = "";
    // for (int i = 0; i < line.length(); i++) { //Not getting last number tho why
    //     if (line[i] != ',') {
    //         temp += line[i];
    //     }
    //     else{
    //         //cout << temp << endl;
    //         float hobby = stof(temp);
    //         hobbies.push_back(hobby);
    //         temp = "";
    //     }
    // }
}

void Person::printVec(){
    for (int i = 0; i < hobbies.size(); i++){
        cout << hobbies[i] << ",";
    }
    cout << endl;
}