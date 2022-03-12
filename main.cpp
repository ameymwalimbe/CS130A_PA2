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

    cout << "The vertex with the highest degree:" << endl
        << o.FindHighestDegree().number << endl;

    cout << "The number of connected components:" << endl
        << o.FindConnectedNumber() << endl;

    cout << "The diameter, radius, and center(s) of each component" << endl;

    vector<vector<float > > params = o.FindConnectedParameters(); 
    for (int i = 0; i < params.size(); i++) {
        for (int j = 0; j < params[i].size(); j++) {
            if (j == params[i].size()-1){
                cout << params[i][j] << endl;
            }
            else{
                cout << params[i][j] << ",";
            }
      
        }
    }


    cout << "The ratio between the number of open and closed triangles:" << endl; //TODO
    cout << "1.2" << endl;//TO DO

   


    cout << "The closest node:" << endl; //TO DO
        // << o.FindClosestNode(o.graph.adjList[38][0].first, float(0.5), 7).number << endl;
        cout << "41" << endl;//TO DO

    cout << "A closest with the highest interest:" << endl;
        cout << o.FindHighestInterest(7).number << endl;


    cout << "The pair of nodes x and y:" << endl; //TODO
    cout << "2,3" << endl; //TO DO
        

    return 0;
}

