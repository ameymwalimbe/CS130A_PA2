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
        sum += (graph.adjList[i].size()-1);
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
    //cout << "created visited array" << endl;
    for (int i = 0; i < graph.adjList.size(); i++){
        if (visited[i] == false){
            DFS(i, visited);
            //cout << "DID DFS" << endl;

            connectedComponents.push_back(comp);
            // for (int j = 0; j < comp.size(); j++){
            //     cout << comp[j] << endl;
            // }
            //cout << "-----------------" << endl;
            comp.clear();

        }
    }
}


void GraphOperator::DFS(int personIndex, vector<bool> & visited) {
    visited[personIndex] = true;
    //cout << "line 86\n";
    comp.push_back(personIndex+1);
    // cout << "line 88\n";
    // cout <<  "size of graph.adjList[personIndex].size(): " << graph.adjList[personIndex].size() << endl;
    for(int i = 0; i < graph.adjList[personIndex].size(); i++){
        //cout << "line 90\n";
        int index = graph.adjList[personIndex][i].first.number - 1;
        //cout << "line 92\n";
        if (!visited[index]){
            //cout << "line 94\n";
            DFS(index, visited);
            //cout << "line 96\n";
        }
    }
    
}

vector<vector<float> > GraphOperator::FindConnectedParameters() { //TO DO
    vector<vector<float> > connectedParameters;

    for (int i = 0; i < connectedComponents.size(); i++){ //Iterating through the outer loop of connected Components
        vector<pair< float, int > > allEccs; 
        float diameter = 0;
        float radius = 99999;
        int center = -1;
        for (int v = 0; v < connectedComponents[i].size(); v++){ //Iterating through individual comp
            int vPerson = connectedComponents[i][v];
            vector <float> shortestPath = dijkstra(vPerson, connectedComponents[i]); //shortest paths from source v to rest of components
            // for (int c = 0; c < shortestPath.size(); c++){
            //     cout << shortestPath[c] << " ";
            // }
            //cout << endl;
            float ecc = float(*max_element(shortestPath.begin(), shortestPath.end())); //find eccentricity for each vertex in one connected component
            pair <float, int> eccPair (ecc, vPerson); //create pair to match eccentricity with corresponding vertex
            allEccs.push_back(eccPair);

            // if (ecc > diameter){
            //     diameter = ecc;
            // }
            // if (ecc < radius){
            //     radius = ecc;
            // }

        }
        vector<float> parameters; // for each componenent 
        for (int e = 0; e < allEccs.size(); e++){
            if (allEccs[e].first > diameter){
                diameter = allEccs[e].first; //find max Eccentricty in the vector 
            }
            if (allEccs[e].first < radius){
                radius = allEccs[e].first; //find min Eccentricity in the vector
                //center = allEccs[e].second;
            }
        }
        
        parameters.push_back(diameter); //push diameter and radius into the parameters vector
        parameters.push_back(radius);

        // find centers by matching ecc to radius of all vertices in componenet
        for (int e = 0; e < allEccs.size(); e++){
            if (std::abs(allEccs[e].first-radius) < 0.001) {
                center = allEccs[e].second;
                parameters.push_back(center); //push each center into the parameters vector
            }
            // if (allEccs[e].first == radius){
            //     center = allEccs[e].second;
            //     parameters.push_back(center); //push each center into the parameters vector
            // }
        }

        connectedParameters.push_back(parameters); //push each parameter vector into the big connectedParameters vector
    }

    return connectedParameters; //has all the connected Parameters for all connected Componenents

}


vector<float> GraphOperator::dijkstra(int vPerson, vector<int> connected) {
    vector<float> returnVector;

    unordered_map<int, float> distances; // dist
    for (int i = 0; i < connected.size(); i++) {
        int personIndex = connected[i];
        if (personIndex == vPerson) {
            distances[vPerson] = float(0);
        }
        else{

            distances[personIndex] = float(99999);
        }
    } //distances initialization works fine

    //distances[vPerson] = 0;
    
    set<int> Visited;
    while (Visited.size() != connected.size()) { //while there are still univisted nodes
        
        float minDistance = float(99999);
        int minPersonIndex = -1;
    
        for (int i = 0; i < connected.size(); i++){ // This for loop finds the minimum distance node 
            if ((distances[connected[i]] < minDistance) && (Visited.count(connected[i]) == 0)){
                minDistance = distances[connected[i]];

                minPersonIndex = connected[i]; 
                //at first run, we grab the source vertex (distance of 0)
            }
        }

        Visited.insert(minPersonIndex);
        for (int v = 1; v < graph.adjList[minPersonIndex-1].size(); v++){ //going thru the min Distance Node's adjList
            if (Visited.count(graph.adjList[minPersonIndex-1][v].first.number) == 0){ //not visited yet
                float vertex = float(graph.adjList[minPersonIndex-1][v].first.number); // vertex set to the v's neighbor
                float vertexWeight = float(graph.adjList[minPersonIndex-1][v].second);  //set vertexWeight to distance from v's neighbor
                if (distances[vertex] > distances[minPersonIndex] + vertexWeight){
                    distances[vertex] = distances[minPersonIndex] + vertexWeight;
                }
            }
        }

    }
    for (int j = 0; j < connected.size(); j++){
            returnVector.push_back(distances[connected[j]]); //push back all the results of dijkstras into returnVector
    }
    
    return returnVector;
}




Person GraphOperator::FindHighestInterest(int h) {
    float maxInterest = 0;
    Person maxPerson;
    for (int i = 0; i < graph.adjList.size(); i++) {
        if (graph.adjList[i][0].first.hobbies[h] >= maxInterest) {
            maxInterest = graph.adjList[i][0].first.hobbies[h];
            maxPerson = graph.adjList[i][0].first;
        }
    }
    return maxPerson;
}

double GraphOperator::FindTrianglesRatio(){ //TO DO (Not working)
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
                        cout << index << endl;
                        closedTriple.insert(jIndex);
                        cout << jIndex << endl; 
                        closedTriple.insert(vIndex);
                        cout << vIndex << endl;
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
    cout << "number of closed triangles: " << closedNum << endl;
    int openNum = openSet.size();
    cout << "number of open triangles: " << openNum << endl;
    //EDGE CASE
    double ratio = openNum/closedNum;
    return ratio;
}

Person GraphOperator::FindClosestNode(Person x, float t, int h) {
    vector<int> newCC;
    vector<bool> visited;
    for (int i = 0; i < graph.adjList.size(); i++){ //Initialize bool vector of visited nodes to be false
        visited.push_back(false); 
    }
    DFS(x.number, visited); //should fill our member variable comp w/ the connected component that Person x is apart of
    
    for (int i = 0; i < comp.size(); i++){
        int personNumber = comp[i];
        if (graph.adjList[personNumber-1][0].first.hobbies[h] >= t) {
            newCC.push_back(personNumber); //newCC now contains only the people (number) that have at least an interest of t on hobby h
        }
    }

    vector<float> distances = dijkstra(x.number, newCC);
    unordered_map<float, Person> d; 
    for (int i = 0; i < newCC.size(); i++){
        int personNumber = newCC[i];
        d[distances[i]] = graph.adjList[personNumber-1][0].first;
    }

    float minEl = 9999;
    for (int v = 0; v <  distances.size(); v++){
        if (distances[v] != 0){ //ignore source vertex distance
            if (distances[v] < minEl){
                minEl = distances[v];
            }
        }
    }
    
    return d[minEl]; //returns minimum distance person that has interest t on h

}


pair<Person, Person> GraphOperator::FindDistanceRatio(){ // find pair of nodes whose ratio between hobby distance and graph distance is smallest
    
}