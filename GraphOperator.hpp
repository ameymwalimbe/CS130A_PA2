#ifndef GRAPHOPERATOR_H
#define GRAPHOPERATOR_H

#include <vector>
#include <unordered_map>
#include "GraphGenerator.hpp"
#include "Person.hpp"
#include <set>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;


class GraphOperator{
    public:
        GraphOperator();
        GraphOperator(GraphGenerator& g); 
        pair<float, vector<Person> >FindAverageDegree(); //Find average degree and the vertex with the highest degree
        vector<Person> FindHighestDegree(); //Find vertex(person) of highest degree(most connections)
        int FindConnectedNumber(); //Find number of connected components
        void DFS(int personIndex, vector<bool> &visited); // helper function for FindConnectedNumber()
        vector<vector<float> > FindConnectedParameters(); //Find Diameter, Radius, Centers of each component
        vector<float> dijkstra(int vPerson, vector<int> connected);
        double FindTrianglesRatio(); // ratio between open and closed triangles
        Person FindClosestNode(Person x, float t, int h); // find closest node from x with an interest level of at least t in hobby h
        Person FindHighestInterest(int h); // find person with the highest interest in hobby h
        pair<Person, Person> FindDistanceRatio(); // find pair of nodes whose ratio between hobby distance and graph distance is smallest

        GraphGenerator graph;
    private:
        bool isEdge(int v1, int v2);
        void CreateConnectedComponents();
        float CalculateHobbyDistance(int v1, int v2);
        //GraphGenerator graph;
        vector<vector<int> > connectedComponents;
        vector<int > comp;

};

#endif