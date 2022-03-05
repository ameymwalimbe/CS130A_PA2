#include <iostream>
#include <fstream>
#include "GraphGenerator.cpp"
#include "GraphOperator.cpp"
//#include "Person.cpp"


using namespace std;
int main(int argc, char *argv[]){
    GraphGenerator g = GraphGenerator(argv[1], argv[2]);
    g.printAdjList();

    GraphOperator o = GraphOperator(g);
    // int numConnect = o.FindConnectedNumber();

    // cout << numConnect << endl;

    return 0;
}