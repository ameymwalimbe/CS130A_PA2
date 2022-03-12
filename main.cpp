#include <iostream>
#include <fstream>
#include "GraphGenerator.hpp"
#include "GraphOperator.hpp"



using namespace std;
int main(int argc, char *argv[]){
    GraphGenerator g = GraphGenerator(argv[1], argv[2]); //create graph

    GraphOperator o = GraphOperator(g); 
    
    cout << "The average degree:" << endl
        << o.FindAverageDegree().first << endl;

    cout << "The vertex with the highest degree:"
        << o.FindHighestDegree().number << endl;

    cout << "The number of connected components:"
        << o.FindConnectedNumber() << endl;

    cout << "The diameter, radius, and center(s) of each componenet:\n";

    vector<vector<float > > params = o.FindConnectedParameters(); 
    for (int i = 0; i < params.size(); i++) {
        for (int j = 0; j < params[i].size(); j++) {
            cout << params[i][j];
        }
        cout << endl;
    }


    cout << "The ratio between the number of open and closed triangles:" << endl; //TODO


    cout << "The closest node:" << endl 
        << o.FindClosestNode(o.graph.adjList[38][0].first, float(0.5), 7).number << endl;

    cout << "The pair of nodes x and y:" << endl; //TODO
        

    return 0;
}

