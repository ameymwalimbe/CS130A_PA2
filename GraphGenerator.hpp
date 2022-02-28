#include <vector>
#include "Person.hpp"
using namespace std;

class GraphGenerator {
    public:
        GraphGenerator();
        GraphGenerator(char* edgesFileName, char* hobbiesFileName);

    private:
        void createAdjList(char* hobbiesFileName); // helper function of constructor- push back the person that corresponds to each index as first entry in each vector of adjList
        void AddEdge(int v1, int v2, double weight);
        vector<vector<Person> > adjList;
};