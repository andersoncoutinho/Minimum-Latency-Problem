#include <iostream>
#include <vector>
#include <algorithm>

#define DEPOT 0

using namespace std;

struct Solution {
  vector<int> circuit;
  double latency;
};

struct Subseq {
    double time;
    double cost;
    double width;
};

struct reOptimization {
    double cost;
    int firstvertex;
    int secondvertex;
};

void fillNeighbourhoods(vector<int> &);
void printTempo(vector<int>, double **);
extern void opt2(reOptimization &, vector<vector<Subseq>>, Solution &, double **);
extern void hSwap(reOptimization &, vector<vector<Subseq>>, Solution &, double **);
extern void reInsertion(reOptimization &, vector<vector<Subseq>>, Solution &, double **);
extern void orOpt2(reOptimization &, vector<vector<Subseq>>, Solution &, double **);
extern void orOpt3(reOptimization &, vector<vector<Subseq>>, Solution &, double **);
extern void fillSubseqInfo(vector<int> &, double **, vector<vector<Subseq>> &, int);

void rvnd(Solution &solution, vector<vector<Subseq>> &subseInfo, double **matrizAdj) {
    
    vector<int> neighbourhoods;
    fillNeighbourhoods(neighbourhoods);
    reOptimization bestNeighbour;
    int aux;

    while(!neighbourhoods.empty()) {
        vector<int> circuit = solution.circuit;
        int neighbourhood = rand() % neighbourhoods.size();

        switch(neighbourhoods[neighbourhood]) {
            case 1:
                opt2(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {
                    reverse(circuit.begin() + bestNeighbour.firstvertex, 
                            circuit.begin() + bestNeighbour.secondvertex+1);

                    solution.latency = bestNeighbour.cost;

                    fillNeighbourhoods(neighbourhoods);
                    fillSubseqInfo(circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);
                    
                } else {

                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);

                }

                break;
            case 2:

                hSwap(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    aux = circuit[bestNeighbour.firstvertex];
                    circuit[bestNeighbour.firstvertex] = circuit[bestNeighbour.secondvertex];
                    circuit[bestNeighbour.secondvertex] = aux;    

                    solution.latency = bestNeighbour.cost;

                    fillNeighbourhoods(neighbourhoods);
                    fillSubseqInfo(circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);

                } else {

                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);

                }

                break;

            case 3:

                reInsertion(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    aux = circuit[bestNeighbour.firstvertex];

                    circuit.erase(circuit.begin() + bestNeighbour.firstvertex);
        
                    circuit.insert(circuit.begin()+bestNeighbour.secondvertex, aux);

                    solution.latency = bestNeighbour.cost;

                    fillNeighbourhoods(neighbourhoods);

                    if(bestNeighbour.firstvertex < bestNeighbour.secondvertex) {
                        
                        fillSubseqInfo(circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);

                    } else {
                        fillSubseqInfo(circuit, matrizAdj, subseInfo, bestNeighbour.secondvertex);
                    }
                                        

                } else {

                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);

                }

                break;
            case 4:

                orOpt2(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    if(bestNeighbour.firstvertex > bestNeighbour.secondvertex) {

                        circuit.insert(circuit.begin()+bestNeighbour.secondvertex,
                                                circuit[bestNeighbour.firstvertex+1]);
                        
                        circuit.insert(circuit.begin()+bestNeighbour.secondvertex,
                                                circuit[bestNeighbour.firstvertex+1]);

                        circuit.erase(circuit.begin() + bestNeighbour.firstvertex+2);
                        circuit.erase(circuit.begin() + bestNeighbour.firstvertex+2);
                        
                        
                    } else {
                        circuit.insert(circuit.begin()+bestNeighbour.secondvertex+1, 
                                                    circuit.begin() +  bestNeighbour.firstvertex,
                                                    circuit.begin() +  bestNeighbour.firstvertex+2);
                                                
                        circuit.erase(circuit.begin() + bestNeighbour.firstvertex);
                        circuit.erase(circuit.begin() + bestNeighbour.firstvertex);
                    }

                    solution.latency = bestNeighbour.cost;                                        
                    
                    fillNeighbourhoods(neighbourhoods);                    
                    
                    if(bestNeighbour.firstvertex < bestNeighbour.secondvertex) {
                        
                        fillSubseqInfo(circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);

                    } else {

                        fillSubseqInfo(circuit, matrizAdj, subseInfo, bestNeighbour.secondvertex);
                    }

                } else {

                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);

                }

                break;
            case 5:

                orOpt3(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    if(bestNeighbour.firstvertex > bestNeighbour.secondvertex) {  
                            
                        circuit.insert(circuit.begin()+bestNeighbour.secondvertex,
                                                circuit[bestNeighbour.firstvertex+2]);
                        
                        circuit.insert(circuit.begin()+bestNeighbour.secondvertex,
                                                circuit[bestNeighbour.firstvertex+2]);
                        
                        circuit.insert(circuit.begin()+bestNeighbour.secondvertex,
                                                circuit[bestNeighbour.firstvertex+2]);
                        
                        circuit.erase(circuit.begin() + bestNeighbour.firstvertex+3);
                        circuit.erase(circuit.begin() + bestNeighbour.firstvertex+3);
                        circuit.erase(circuit.begin() + bestNeighbour.firstvertex+3);

                    } else {
                        circuit.insert(circuit.begin()+bestNeighbour.secondvertex+1, 
                                                    circuit.begin() +  bestNeighbour.firstvertex,
                                                    circuit.begin() +  bestNeighbour.firstvertex+3);
                                                           
                        circuit.erase(circuit.begin() + bestNeighbour.firstvertex);
                        circuit.erase(circuit.begin() + bestNeighbour.firstvertex);
                        circuit.erase(circuit.begin() + bestNeighbour.firstvertex);
                    }

                    solution.latency = bestNeighbour.cost;

                    fillNeighbourhoods(neighbourhoods);
                    
                    if(bestNeighbour.firstvertex < bestNeighbour.secondvertex) {
                        
                        fillSubseqInfo(circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);

                    } else {
                        fillSubseqInfo(circuit, matrizAdj, subseInfo, bestNeighbour.secondvertex);
                    }

                } else {

                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);

                }

                break;
        }
        solution.circuit = circuit;
    }
}

void fillNeighbourhoods(vector<int> &neighbourhoods) {
    neighbourhoods = {1, 2, 3, 4, 5};
}