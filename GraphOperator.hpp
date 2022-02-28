#include <vector>
#include "GraphGenerator.hpp"

using namespace std;

class GraphOperator{
    public:
        GraphOperator();
        GraphOperator(GraphGenerator& g);
        pair<int, Person> FindAverageDegree(); //Find average degree and the vertex with the highest degree
        Person FindHighestDegree(); //Find vertex(person) of highest degree(most connections)
        int FindConnectedNumber(); //Find number of connected components
        vector<vector<int> > FindConnectedParameters(); //Find Diameter, Radius, Centers of each component
        double FindTrianglesRatio(); // ratio between open and closed triangles
        Person FindClosestNode(Person x, int t, int h); // find closest node from x with an interest level of at least t in hobby h
        Person FindHighestInterest(int h); // find person with the highest interest in hobby h
        pair<Person, Person> FindDistanceRatio(); // find pair of nodes whose ratio between hobby distance and graph distance is smallest

    private:
        GraphGenerator *graph;

};