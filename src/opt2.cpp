#include <iostream>
#include <vector>
#include <algorithm>
#include "./Headers/structures.h"

void opt2(reOptimization &bestNeighbour, vector<vector<Subseq>> subseqInfo, Solution &solution, double **matrizAdj) {
    
    int bestI, bestJ, dimension = solution.circuit.size()-1;
    double cost, bestCost = __DBL_MAX__;
    vector<int> circuit = solution.circuit;

    for(int i = 1; i < dimension - 3; i++) {
        
        for(int j = i + 3; j < dimension; j++) {
            
            cost = subseqInfo[DEPOT][i-1].cost
                    +subseqInfo[j][i].width * (subseqInfo[DEPOT][i-1].time + matrizAdj[circuit[i-1]][circuit[j]])
                    +subseqInfo[j][i].cost
                    +subseqInfo[j+1][dimension].width * (subseqInfo[DEPOT][i-1].time
                                                                +matrizAdj[circuit[i-1]][circuit[j]]
                                                                +subseqInfo[j][i].time
                                                                +matrizAdj[circuit[i]][circuit[j+1]])
                    +subseqInfo[j+1][dimension].cost
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