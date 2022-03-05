#include <fstream>
#include <sstream>
#include "GraphGenerator.hpp"


GraphGenerator::GraphGenerator(char* edgesFileName, char* hobbiesFileName){
    createAdjList(hobbiesFileName);
    addEdge(edgesFileName);
}

void GraphGenerator::createAdjList(char* hobbiesFileName) {
    ifstream hobbyFile;

    hobbyFile.open(hobbiesFileName);
    string line = "";
    int i = 0;
    if (hobbyFile.is_open()){
        while (!hobbyFile.eof()) {
            getline(hobbyFile, line);
            Person myPerson = Person(line, i);
            pair <Person, float> myPair (myPerson, 1.0);
            adjList.push_back(vector< pair <Person, float> >());
            adjList[i].push_back(myPair); //insert Person, 1.0 into the first index
            i++;
        }
        hobbyFile.close(); 
    }
    else{
        cout << "no try again." << endl;
    }
    
}

void GraphGenerator::addEdge(char* edgesFileName){
    ifstream edgesFile;
    edgesFile.open(edgesFileName);

    string line = "";
    if (edgesFile.is_open()){
        while (!edgesFile.eof()) {
            vector<float> varList;
            getline(edgesFile, line);
            stringstream ss (line);
            float f;
            while(ss>>f){
                if (ss.peek() == ','){
                    ss.ignore();
                }
                varList.push_back(f);
            } 
            int v1 = varList.at(0);
            cout << v1 << endl;
            int v2 = varList.at(1);
            float weight = varList.at(2);

            pair <Person, float> myPair1 (adjList[v1-1][0].first, weight);
            pair <Person, float> myPair2 (adjList[v2-1][0].first, weight);

            adjList[v1-1].push_back(myPair2);
            adjList[v2-1].push_back(myPair1);    
        }   
    }

    else {
        cout << "EdgesFile not open\n";
    }

    edgesFile.close();
}

void GraphGenerator::printAdjList(){
    for (int i = 0; i < adjList.size(); i++){
        for (int j = 0; j < adjList[i].size(); j++){
            cout << adjList[i][j].second << endl;
        }
    }
}
