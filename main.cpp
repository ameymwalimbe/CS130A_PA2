#include <iostream>
#include <fstream>
#include "GraphGenerator.hpp"
#include "GraphOperator.hpp"



using namespace std;
int main(int argc, char *argv[]){
    GraphGenerator g = GraphGenerator(argv[1], argv[2]); //create graph
    //g.printAdjList();

    GraphOperator o = GraphOperator(g); 
    //cout << "here\n";
    // int numConnect = o.FindConnectedNumber();
    // pair<int, Person> average = o.FindAverageDegree();
    // //double ratio = o.FindTrianglesRatio();
    // int hobby = 3;
    // Person myPerson = o.FindHighestInterest(hobby);
    // cout << "person with highest interest in hobby " <<  hobby << " is " << myPerson.number << endl;

    vector<vector<int> > ccv;
    ccv = o.FindConnectedParameters();
    // cout << "ccv.size(): " << ccv.size() << endl;
    // for (int i = 0; i < ccv.size(); i++) {
    //     for (int j = 0; j< ccv[i].size(); j++) {
    //         cout << ccv[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    
    //cout << "triangles ratio: " << ratio << endl;
    
    // cout << "average degree: " << average.first
    //     << " Person: " << average.second.number  << endl;

    // cout << "num Connected: " << numConnect << endl;
    



    return 0;
}

