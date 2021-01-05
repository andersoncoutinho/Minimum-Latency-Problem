#include <iostream>
#include <vector>
#include <algorithm>
#include "../Headers/functions.h"

#define DEPOT 0

void rvnd(Solution &solution, vector<vector<Subseq>> &subseInfo, double **matrizAdj) {
    
    vector<int> neighbourhoods;
    fillNeighbourhoods(neighbourhoods);
    reOptimization bestNeighbour;

    while(!neighbourhoods.empty()) {
        bestNeighbour.cost = solution.latency;
        int neighbourhood = rand() % neighbourhoods.size();

        switch(neighbourhoods[neighbourhood]) {
            case 1:
                opt2(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    opt2Move(solution, bestNeighbour);                    
                    fillNeighbourhoods(neighbourhoods);
                    fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);    

                } else {
                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);
                }
                break;
            case 2:
                hSwap(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    hSwapMove(solution, bestNeighbour);
                    fillNeighbourhoods(neighbourhoods);
                    fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, bestNeighbour.firstvertex);

                } else {
                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);
                }
                break;
            case 3:
                reInsertion(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    reInsertionMove(solution, bestNeighbour);                    

                    fillNeighbourhoods(neighbourhoods);
                    fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, firstVertex(bestNeighbour));
                    
                } else {
                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);
                }
                break;
            case 4:
                orOpt2(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    orOpt2Move(solution, bestNeighbour);                                        
                    
                    fillNeighbourhoods(neighbourhoods);                    
                    fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, firstVertex(bestNeighbour));

                } else {
                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);
                }
                break;
            case 5:
                orOpt3(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {

                    orOpt3Move(solution, bestNeighbour);

                    fillNeighbourhoods(neighbourhoods);
                    fillSubseqInfo(solution.circuit, matrizAdj, subseInfo, firstVertex(bestNeighbour));

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

int firstVertex(reOptimization bestNeighbour) {
    return ((bestNeighbour.firstvertex < bestNeighbour.secondvertex) ? bestNeighbour.firstvertex
                                                                     : bestNeighbour.secondvertex);
}