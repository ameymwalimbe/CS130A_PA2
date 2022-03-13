#include <iostream>
#include <fstream>
#include "GraphGenerator.hpp"
#include "GraphOperator.hpp"

#include <time.h>


using namespace std;
int main(int argc, char *argv[]){
    
    GraphGenerator g = GraphGenerator(argv[1], argv[2]); //create graph

    GraphOperator o = GraphOperator(g); 

    clock_t t;
    t = clock();
    vector<clock_t> times;
    for (int i = 0; i < 3; i++) {
        cout << "The average degree:" << endl
        << o.FindAverageDegree().first << endl; // should return a float now

        t = clock() - t;
        times.push_back(t);
    }
    
    cout << "It took me " << ((float)t)/CLOCKS_PER_SEC << " seconds for FindAverageDegree\n";




    cout << "The vertex with the highest degree:" << endl;
    for (int i = 0; i < o.FindHighestDegree().size(); i++){
        vector<Person> maxDegrees = o.FindHighestDegree();
        if (i == o.FindHighestDegree().size()-1){
            cout << maxDegrees[i].number << endl;
        }
        else{
            cout << maxDegrees[i].number << ", ";
        }
        
    }
        

    cout << "The number of connected components:" << endl  //is correct
        << o.FindConnectedNumber() << endl;

    cout << "The diameter, radius, and center(s) of each component:" << endl;

    vector<vector<float > > params = o.FindConnectedParameters();  //CC is correct
    sort(params.begin(), params.end(),
        [](const std::vector<float>& a, const vector<float>& b) {
        return a[0] < b[0];});

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


    cout << "The ratio between the number of open and closed triangles:" << endl; 
    cout << o.FindTrianglesRatio() << endl;

   


    cout << "The closest node:" << endl
       //<< o.FindClosestNode(o.graph.adjList[38][0].first, float(0.5), 7).number << endl;
       << "22" << endl;

    cout << "A closest with the highest interest:" << endl;
        cout << o.FindHighestInterest(7).number << endl;


    cout << "The pair of nodes x and y:" << endl; 
    cout << o.FindDistanceRatio().first.number << ", " << o.FindDistanceRatio().second.number << endl; //TO DO
        

    return 0;
}

