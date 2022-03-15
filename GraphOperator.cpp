#include "GraphOperator.hpp"
#include <unordered_map>



GraphOperator::GraphOperator() {};

GraphOperator::GraphOperator(GraphGenerator& g) {
    graph = g; //initialize private variables
    CreateConnectedComponents(); //fills the connected components set w/ all the connected vertices

}

pair<float, vector<Person> > GraphOperator::FindAverageDegree() {
    //Find average degree and the vertex with the highest degree
    float sum = 0;
    for (int i = 0; i < graph.adjList.size(); i++) {
        sum += (graph.adjList[i].size()-1);
    }
    float avg = sum / (graph.adjList.size()); 
    vector<Person> maxPerson = FindHighestDegree();
    pair <float, vector<Person> > returnPair (avg, maxPerson);

    return returnPair; 
}

vector<Person> GraphOperator::FindHighestDegree() {
//Find vertex(person) of highest degree(most connections)
    vector<Person> maxDegrees;
    int max = 0;


    for (int i = 0; i < graph.adjList.size(); i++) {
        if (graph.adjList[i].size() >= max) {
            max = graph.adjList[i].size();
            
        }
    }
    for (int v = 0; v < graph.adjList.size(); v++){
        if (graph.adjList[v].size() == max){
            maxDegrees.push_back(graph.adjList[v][0].first);
        }
    }
    return maxDegrees;
}

int GraphOperator::FindConnectedNumber() {
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


void GraphOperator::DFS(int personIndex, vector<bool> & visited) {
    visited[personIndex] = true;
    //cout << "line 86\n";
    comp.push_back(personIndex+1);
    // cout << "line 88\n";
    // cout <<  "size of graph.adjList[personIndex].size(): " << graph.adjList[personIndex].size() << endl;
    for(int i = 0; i < graph.adjList[personIndex].size(); i++){

        int index = graph.adjList[personIndex][i].first.number - 1;
      
        if (!visited[index]){
        
            DFS(index, visited);
       
        }
    }
    
}

vector<vector<float> > GraphOperator::FindConnectedParameters() { 
    vector<vector<float> > connectedParameters;

    for (int i = 0; i < connectedComponents.size(); i++){ //Iterating through the outer loop of connected Components
        vector<pair< float, int > > allEccs; 
        float diameter = 0;
        float radius = 99999;
        int center = -1;
        for (int v = 0; v < connectedComponents[i].size(); v++){ //Iterating through individual comp
            int vPerson = connectedComponents[i][v];
            vector <float> shortestPath = dijkstra(vPerson, connectedComponents[i]); //shortest paths from source v to rest of components
   
            float ecc = float(*max_element(shortestPath.begin(), shortestPath.end())); //find eccentricity for each vertex in one connected component
            pair <float, int> eccPair (ecc, vPerson); //create pair to match eccentricity with corresponding vertex
            allEccs.push_back(eccPair);

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
        }

        connectedParameters.push_back(parameters); //push each parameter vector into the big connectedParameters vector
    }

    return connectedParameters; //has all the connected Parameters for all connected Componenents

}


vector<float> GraphOperator::dijkstra(int vPerson, vector<int> connected) {
    vector<float> returnVector;


    unordered_map<int, float> distances; // dist
    for (int i = 0; i < connected.size(); i++) {
        //cout << "line 148\n";
        int personIndex = connected[i];
        if (personIndex == vPerson) {
            distances[vPerson] = float(0);
            //cout << "yes " << endl;
        }
        else{

            distances[personIndex] = float(99999);
        }
    } //distances initialization works fine

    
    set<int> Visited;
    while (Visited.size() != connected.size()) { //while there are still univisted nodes

        float minDistance = float(99999);
        int minPersonIndex = -1;
        for (int i = 0; i < connected.size(); i++){ // This for loop finds the minimum distance node 
            //cout << Visited.count(connected[i]) << endl;
            if ((distances[connected[i]] < minDistance) && (Visited.count(connected[i]) == 0)){
                
                minDistance = distances[connected[i]];

                minPersonIndex = connected[i]; 
                //at first run, we grab the source vertex (distance of 0)
            }
        }
        //cout << "minPersonIndex: " << minPersonIndex << endl;
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
        if (graph.adjList[i][0].first.hobbies[h-1] > maxInterest) {
            maxInterest = graph.adjList[i][0].first.hobbies[h-1];
            maxPerson = graph.adjList[i][0].first;
        }
    }
    return maxPerson;
}
bool GraphOperator::isEdge(int v1, int v2){
    for (int i = 1; i < graph.adjList[v1-1].size(); i++){
        if (graph.adjList[v1-1][i].first.number == v2){
            return true;
        }
    }
    return false;
}
double GraphOperator::FindTrianglesRatio(){ 
    //Iterate thru nodes from the adjList
        //Go through node's neighbors (select 2)
            //go through one of the neighbor's adjList, check if the second node exists 
                //if yes --> increment closed by one
                //if no --> increment open by one

    float closedCount = 0;
    float openCount= 0;
    for (int i = 0; i < graph.adjList.size(); i++){

       
        for (int c = 1; c < graph.adjList[i].size(); c++){ //neighbor1
      
            for (int j = c+1; j < graph.adjList[i].size(); j++){ //neighbor2

                    if (isEdge(graph.adjList[i][c].first.number, graph.adjList[i][j].first.number)){
                        closedCount++;
                    }
                    else{
                        openCount++;
                    }
         
                
            }
        }
    }

    float returnVal = 3*(openCount/closedCount); 
    return returnVal;
}

            

    

Person GraphOperator::FindClosestNode(Person x, float t, int h) {
 
    comp.clear();
    vector<int> newCC;
    vector<bool> visited;
    vector<Person> results;
    for (int i = 0; i < graph.adjList.size(); i++){ //Initialize bool vector of visited nodes to be false
        visited.push_back(false); 
 
    }
    
    DFS(x.number-1, visited); //should fill our member variable comp w/ the connected component that Person x is apart of

    if (graph.adjList[x.number-1][0].first.hobbies[h-1] < t){//person x doesnt meet the requirements, needs to be manually entered into newCC
    
        newCC.push_back(x.number);
    } 

    if (graph.adjList[x.number-1][0].first.hobbies[h-1] >= t){ //Person x does meet the requirements
        results.push_back(x);
    }

    for (int i = 0; i < comp.size(); i++){
        int personNumber = comp[i];
        if (graph.adjList[personNumber-1][0].first.hobbies[h-1] >= t) {
            newCC.push_back(personNumber); //newCC now contains only the people (number) that have at least an interest of t on hobby h
        }
    }

    vector<float> distances = dijkstra(x.number, newCC);



    vector<pair<Person, float> > d;

    for (int i = 0; i < newCC.size(); i++){;
        int personNumber = newCC[i];
        //d[distances[i]] = graph.adjList[personNumber-1][0].first;
        //d[graph.adjList[personNumber-1][0].first] = distances[i];
        pair<Person, float> distPair(graph.adjList[personNumber-1][0].first, distances[i]);
        d.push_back(distPair);
    }

    float minDist = 9999;
    int minPerson = -1;
    for (int i = 0; i < d.size(); i++) {
        float curDist = d[i].second; 
        if ((curDist < minDist) && (d[i].first.number != x.number)) {
            minDist = curDist;
            minPerson = d[i].first.number;
        }
    }
    results.push_back(graph.adjList[minPerson-1][0].first);
    int min = 9999;
    for (int p = 0; p < results.size(); p++){
        if (results[p].number < min){
            min = results[p].number;
        }
    }
    return graph.adjList[min-1][0].first;


}


pair<Person, Person> GraphOperator::FindDistanceRatio(){ // find pair of nodes whose ratio between hobby distance and graph distance is smallest
    //minRatio = INF
    //iterate thru our CONNECTED COMPONENTS
        //iterate thru our individual components
            //run dijkstras --> distances from source vertex
            //iterate through the same individual components again
                // calculate the hobby distance between source vertex and another vertex
                //calculate distance ratio for that source vertex and other vertex
                // if currRatio < minRatio, update minRatio

    pair<Person, Person> returnPair(graph.adjList[0][0].first, graph.adjList[0][0].first);
    float minRatio = 9999; 
    for (int i = 0; i < connectedComponents.size(); i++) {
        for (int j = 0; j < connectedComponents[i].size(); j++) {
            sort(connectedComponents[i].begin(), connectedComponents[i].end());
            vector<float> distances = dijkstra(connectedComponents[i][j], connectedComponents[i]);
            for (int k = j+1; k < connectedComponents[i].size(); k++) {
 
                float hobbyD = CalculateHobbyDistance(connectedComponents[i][j], connectedComponents[i][k]);
                float curDistRatio = hobbyD/distances[k];
                // cout << "hobbyD: " << hobbyD << " | "
                //     << "distances[k]: " << distances[k] << " | "
                //     << "curDistRatio: " << curDistRatio 
                //     << " components being looked at: " << connectedComponents[i][j] << " and " << connectedComponents[i][k] << endl;
                if (curDistRatio < minRatio){
                    returnPair.first = graph.adjList[connectedComponents[i][j]-1][0].first;
                    returnPair.second = graph.adjList[connectedComponents[i][k]-1][0].first;
                    minRatio = curDistRatio;

                }
            }
        }
    }
    return returnPair;
}

float GraphOperator::CalculateHobbyDistance(int v1, int v2){ //helper function for FindDistanceRatio
    float sum = 0;
    int hobbyLength = graph.adjList[v1-1][0].first.hobbies.size();
    for (int i = 0; i < hobbyLength; i++) {
        float diffSq = 0;
        float h1 = graph.adjList[v1-1][0].first.hobbies[i];
        float h2 = graph.adjList[v2-1][0].first.hobbies[i];
        diffSq = (h1 - h2) * (h1 - h2);
        sum += diffSq;
    }

    float returnVal = sqrt(sum);

    return returnVal;
}