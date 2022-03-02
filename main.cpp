#include <iostream>
#include <fstream>
#include "GraphGenerator.cpp"
//#include "Person.cpp"


using namespace std;
int main(int argc, char *argv[]){
    GraphGenerator g = GraphGenerator(argv[1], argv[2]);
    g.printAdjList();
    return 0;
}