#include "GraphOperator.hpp"

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