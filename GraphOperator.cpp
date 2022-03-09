#include "GraphOperator.hpp"
#include <set>

GraphOperator::GraphOperator() {};

GraphOperator::GraphOperator(GraphGenerator& g) {
    graph = g; //initialize private variables
}

pair<int, Person> GraphOperator::FindAverageDegree() {
    //Find average degree and the vertex with the highest degree
    int sum = 0;
    for (int i = 0; i < graph.adjList.size(); i++) {
        sum += graph.adjList[i].size();
    }
    int avg = sum / (graph.adjList.size());
    Person maxPerson = FindHighestDegree();
    pair <int, Person> returnPair (avg, maxPerson);

    return returnPair;
}

Person GraphOperator::FindHighestDegree() {
//Find vertex(person) of highest degree(most connections)
    int max = 0;
    Person maxPerson;

    for (int i = 0; i < graph.adjList.size(); i++) {
        if (graph.adjList[i].size() >= max) {
            max = graph.adjList[i].size();
            maxPerson = graph.adjList[i][0].first; //What if theres multiple ppl with max degrees?
        }
    }
    return maxPerson;
}

int GraphOperator::FindConnectedNumber() {
    //Find number of connected components
    //Use DFS   

    int numConnect = 0;
    vector<bool> visited;
    for (int i = 0; i < graph.adjList.size(); i++){ //Initialize bool vector of visited nodes to be false
        visited.push_back(false); 
    } 
    for (int i = 0; i < graph.adjList.size(); i++){
        if (visited[i] == false){
            DFS(i, visited);
            numConnect++;

        }
    }

    return numConnect;

}

void GraphOperator::DFS(int personIndex, vector<bool> visited) {
    visited[personIndex] = true;

    for (int i = 0; i < graph.adjList[personIndex].size(); i++){
        int index = graph.adjList[personIndex][i].first.number;

        if (!visited[index]){
            DFS(index, visited);
        }
    }
    
}

vector<vector<int> > GraphOperator::FindConnectedParameters() {
}


Person GraphOperator::FindHighestInterest(int h) {
    int maxInterest = 0;
    Person maxPerson;
    for (int i = 0; i < graph.adjList.size(); i++) {
        if (graph.adjList[i][0].first.hobbies[h] > maxInterest) {
            maxInterest = graph.adjList[i][0].first.hobbies[h];
            maxPerson = graph.adjList[i][0].first;
        }
    }
    return maxPerson;
}

double GraphOperator::FindTrianglesRatio(){
    int countClosed = 0;
    int countOpen = 0;

    set<set<int> > closedSet;
    set<set<int> > openSet;
    
    for (int v = 0; v < graph.adjList.size(); v++){
        for (int i = 1; i < graph.adjList[v].size(); i++){
            int index = graph.adjList[v][i].first.number;
            for (int j = 1; j < graph.adjList[index].size(); j++){
                int jIndex = graph.adjList[index][j].first.number;
                for (int k = 1; k < graph.adjList[jIndex].size(); k++){
                    int vIndex = graph.adjList[v][0].first.number;
                    if (graph.adjList[jIndex][k].first.number == graph.adjList[v][0].first.number){
                        
                        set<int> closedTriple;
                        closedTriple.insert(index);
                        closedTriple.insert(jIndex); 
                        closedTriple.insert(vIndex);
                        closedSet.insert(closedTriple); //inserted the closedTriangle verts into the set
                        
                    }
                    else{
                        //countOpen++;
                        set<int> openTriple;
                        openTriple.insert(index);
                        openTriple.insert(jIndex); 
                        openTriple.insert(vIndex);
                        closedSet.insert(openTriple); //inserted the closedTriangle verts into the set
                    }
                }
            }
        }
    }


    int closedNum = closedSet.size();
    int openNum = openSet.size();

    double ratio = openNum/closedNum;
    return ratio;
}