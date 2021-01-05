#include <iostream>
#include <vector>
#include <algorithm>
#include "../Headers/structures.h"

#define DEPOT 0

using namespace std;

void opt2(reOptimization &bestNeighbour, vector<vector<Subseq>> subseqInfo, Solution &solution, double **matrizAdj) {
    
    int bestI, bestJ;
    vector<int> circuit = solution.circuit;
    int solutionSize = solution.circuit.size();

    double cost, bestCost = __DBL_MAX__;

    for(int i = 1; i < solutionSize - 4; i++) {
        
        for(int j = i + 3; j < solutionSize-1; j++) {
            
            cost = subseqInfo[DEPOT][i-1].cost
                    +subseqInfo[j][i].width * (subseqInfo[DEPOT][i-1].time + matrizAdj[circuit[i-1]][circuit[j]])
                    +subseqInfo[j][i].cost
                    +subseqInfo[j+1][solutionSize-1].width * (subseqInfo[DEPOT][i-1].time
                                                                +matrizAdj[circuit[i-1]][circuit[j]]
                                                                +subseqInfo[j][i].time
                                                                +matrizAdj[circuit[i]][circuit[j+1]])
                    +subseqInfo[j+1][solutionSize-1].cost
                    ;
            
            if(cost < bestCost) {
                bestI = i;
                bestJ = j;
                bestCost = cost;
            }
        }
    }
    bestNeighbour.firstvertex = bestI;
    bestNeighbour.secondvertex = bestJ;
    bestNeighbour.cost = bestCost;
}