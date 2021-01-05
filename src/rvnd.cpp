#include <iostream>
#include <vector>
#include <algorithm>
#include "../Headers/functions.h"


#define DEPOT 0

void rvnd(Solution &solution, vector<vector<Subseq>> &subseInfo, double **matrizAdj) {
    
    vector<int> neighbourhoods;
    fillNeighbourhoods(neighbourhoods);
    reOptimization bestNeighbour;
    int aux;

    while(!neighbourhoods.empty()) {
        
        int neighbourhood = rand() % neighbourhoods.size();

        switch(neighbourhoods[neighbourhood]) {
            case 1:
                opt2(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {
                    reverse(solution.circuit.begin() + bestNeighbour.firstvertex, 
                            solution.circuit.begin() + bestNeighbour.secondvertex+1);

                    solution.latency = bestNeighbour.cost;

                    fillNeighbourhoods(neighbourhoods);
                    fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);
                    
                } else {
                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);
                }
                break;
            case 2:
                hSwap(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    aux = solution.circuit[bestNeighbour.firstvertex];
                    solution.circuit[bestNeighbour.firstvertex] = solution.circuit[bestNeighbour.secondvertex];
                    solution.circuit[bestNeighbour.secondvertex] = aux;    

                    solution.latency = bestNeighbour.cost;

                    fillNeighbourhoods(neighbourhoods);
                    fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);

                } else {
                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);
                }
                break;
            case 3:
                reInsertion(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    aux = solution.circuit[bestNeighbour.firstvertex];

                    solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);
        
                    solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex, aux);

                    solution.latency = bestNeighbour.cost;

                    fillNeighbourhoods(neighbourhoods);

                    if(bestNeighbour.firstvertex < bestNeighbour.secondvertex) {                        
                        fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);
                    } else {
                        fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, bestNeighbour.secondvertex);
                    }

                } else {
                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);
                }
                break;
            case 4:
                orOpt2(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    if(bestNeighbour.firstvertex > bestNeighbour.secondvertex) {

                        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex,
                                                solution.circuit[bestNeighbour.firstvertex+1]);
                        
                        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex,
                                                solution.circuit[bestNeighbour.firstvertex+1]);

                        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex+2);
                        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex+2);
                        
                        
                    } else {
                        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex+1, 
                                                    solution.circuit.begin() +  bestNeighbour.firstvertex,
                                                    solution.circuit.begin() +  bestNeighbour.firstvertex+2);
                                                
                        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);
                        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);
                    }

                    solution.latency = bestNeighbour.cost;                                        
                    
                    fillNeighbourhoods(neighbourhoods);                    
                    
                    if(bestNeighbour.firstvertex < bestNeighbour.secondvertex) {                        
                        fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);
                    } else {
                        fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, bestNeighbour.secondvertex);
                    }

                } else {
                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);
                }
                break;
            case 5:
                orOpt3(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    if(bestNeighbour.firstvertex > bestNeighbour.secondvertex) {  
                            
                        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex,
                                                solution.circuit[bestNeighbour.firstvertex+2]);
                        
                        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex,
                                                solution.circuit[bestNeighbour.firstvertex+2]);
                        
                        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex,
                                                solution.circuit[bestNeighbour.firstvertex+2]);
                        
                        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex+3);
                        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex+3);
                        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex+3);

                    } else {
                        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex+1, 
                                                    solution.circuit.begin() +  bestNeighbour.firstvertex,
                                                    solution.circuit.begin() +  bestNeighbour.firstvertex+3);
                                                           
                        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);
                        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);
                        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);
                    }

                    solution.latency = bestNeighbour.cost;

                    fillNeighbourhoods(neighbourhoods);
                    
                    if(bestNeighbour.firstvertex < bestNeighbour.secondvertex) {                        
                        fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);
                    } else {
                        fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, bestNeighbour.secondvertex);
                    }

                } else {
                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);
                }
                break;
        }
    }
}

void fillNeighbourhoods(vector<int> &neighbourhoods) {
    neighbourhoods = {1, 2, 3, 4, 5};
}