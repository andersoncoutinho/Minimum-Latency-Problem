#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Solution {
  vector <int> circuit;
  double latency;
};

struct InsertionInfo {
    int insertedVertex;
    double cost;
};

bool Compare(InsertionInfo v1, InsertionInfo v2);
double calculateLatency(vector<int> circuit, double **matrizAdj);

void construction(Solution &solution, int dimension, double **matrizAdj) {

    double alfa = (rand() % 101)/(double) 100;    
    vector<int> circuit;
    vector<int> candidates;
    int lastVertex;

    circuit.push_back(1);
    lastVertex = 1;

    for(int i = 2; i <= dimension; i++) {
        candidates.push_back(i);
    }

    while(!candidates.empty()) {

        vector<InsertionInfo> insertionInfo;
        
        for(int i = 0; i < candidates.size(); i++) {
            insertionInfo.push_back({i, matrizAdj[candidates[i]][lastVertex]});
        }

        sort(insertionInfo.begin(), insertionInfo.end(), Compare);

        int n = (int)(alfa * insertionInfo.size());
        int N = n != 0 ? (rand() % n) : 0; 

        circuit.push_back(candidates[insertionInfo[N].insertedVertex]);
        lastVertex = candidates[insertionInfo[N].insertedVertex];
        candidates.erase(candidates.begin() + insertionInfo[N].insertedVertex);

    }

    circuit.push_back(1);
    
    solution.circuit = circuit;
}

bool Compare(InsertionInfo v1, InsertionInfo v2) {
    return v1.cost < v2.cost;
}

double calculateLatency(vector<int> circuit, double **matrizAdj) {
    double cost = 0;
    for(int i = 0; i < circuit.size()-1; i++) {
        cost += matrizAdj[circuit[i]][circuit[i+1]];
    }
    return cost;
}