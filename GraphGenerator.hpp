#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <vector>
#include "Person.hpp"
using namespace std;

class GraphGenerator {
    public:
        GraphGenerator();
        GraphGenerator(char* edgesFileName, char* hobbiesFileName);
        void printAdjList();

        void createAdjList(char* hobbiesFileName); // helper function of constructor- push back the person that corresponds to each index as first entry in each vector of adjList
        void addEdge(char* edgesFileName);
        vector<vector< pair <Person, float> > > adjList;
}; 

#endif