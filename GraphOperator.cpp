#include "GraphOperator.hpp"


GraphOperator::GraphOperator() {};

GraphOperator::GraphOperator(GraphGenerator& g) {
    graph = g; //initialize private variables
    CreateConnectedComponents(); //fills the connected components set w/ all the connected vertices

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

    // int numConnect = 0;
    // vector<bool> visited;
    // for (int i = 0; i < graph.adjList.size(); i++){ //Initialize bool vector of visited nodes to be false
    //     visited.push_back(false); 
    // } 
    // for (int i = 0; i < graph.adjList.size(); i++){
    //     if (visited[i] == false){
    //         DFS(i, visited);
    //         numConnect++;

    //     }
    // }

    // return numConnect;
    return connectedComponents.size();

}

void GraphOperator::CreateConnectedComponents(){
    vector<bool> visited;
    for (int i = 0; i < graph.adjList.size(); i++){ //Initialize bool vector of visited nodes to be false
        visited.push_back(false); 
    } 
    for (int i = 0; i < graph.adjList.size(); i++){
        if (visited[i] == false){
            DFS(i, visited);
            connectedComponents.push_back(comp);
            comp.clear();

        }
    }
}


void GraphOperator::DFS(int personIndex, vector<bool> visited) {
    visited[personIndex] = true;;
    comp.push_back(personIndex);
    for(int i = 0; i < graph.adjList[personIndex].size(); i++){
        int index = graph.adjList[personIndex][i].first.number;

        if (!visited[index]){
            DFS(index, visited);
        }
    }
    
}

vector<vector<int> > GraphOperator::FindConnectedParameters() {
    vector<pair < int, int > > eccs;

    for (int i = 0; i < connectedComponents.size(); i++){ //Iterating through the outer loop of connected Components

        for (int v = 0; v < connectedComponents[i].size(); v++){ //Iterating through a s
            int maxEcc = 0;
            int vPerson = connectedComponents[i][v];
            unordered_map<int, int> temp = dijkstra(vPerson);
            

            if (temp > maxEcc){
                maxEcc = temp;
            }
        }
            
            pair<int,int> eccPair (vPerson, maxEcc);
            eccs.push_back(eccPair);
        }
    }



vector<int> GraphOperator::dijkstra(int vPerson) {
    vector<int> returnVector;

    // returns shortest distance between the 2 people
    vector<int> tempConnectedComponents;
    vector<int> ;
    for (int i = 0; i < connectedComponents.size(); i++) {
        for (int j = 0; j < connectedComponents[i].size(); j++) {
            if (vPerson == connectedComponents[i][j]) {
                for (int k = 0; k < connectedComponents[i].size(); k++)
                    tempConnectedComponents.push_back(connectedComponents[i][k]);
            }
            break; //put the relevant connected components into tempConnected
        } 
    }
    //hashtable with all vertex: distance 
    unordered_map<int, int> distances;
    for (int i = 0; i < tempConnectedComponents.size(); i++) {
        int personIndex = tempConnectedComponents[i];
        if (personIndex != vPerson) {
            distances[personIndex] = 9999999;
        }
        else{
            distances[personIndex] = 0;
        }
    }
    
    vector<int> tempConnectedComponentsCopy  = tempConnectedComponents;
    //run dijkstras
    set<int> Visited;

    //while (tempConnectedComponents.size() > 0){
    while (tempConnectedComponents.size() >0){
    
        int minDistance = 99999;
        int minPersonIndex = -1;
 
        for (int i = 0; i < tempConnectedComponents.size(); i++){ // This for loop finds the minimum distance node 
            if (distances[tempConnectedComponents[i]] < minDistance){
                minDistance = distances[tempConnectedComponents[i]];
                tempConnectedComponents[i] = -1;
                minPersonIndex = tempConnectedComponents[i];
            }
        }
        
        Visited.insert(minPersonIndex); //insert min Distance Node into the Visited set
        for (int v = 1; v < graph.adjList[minPersonIndex].size(); v++){ //going thru the min Distance Node's adjList
            int vertex = graph.adjList[minPersonIndex][v].first.number; // vertex set to the neighbor
            int vertexWeight = graph.adjList[minPersonIndex][v].second;
            if (distances[vertex] > distances[minPersonIndex] + vertexWeight){
                distances[vertex] = distances[minPersonIndex] + vertexWeight;
                tempConnectedComponents.pop(minPersonIndex);
                
            }
        }

        for (int j = 0; j < tempConnectedComponentsCopy.size(); j++){
            returnVector.push_back(distances[tempConnectedComponents[j]]);
        }
        
    }
   
    return returnVector;  
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

