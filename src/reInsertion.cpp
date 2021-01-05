#include <iostream>
#include <vector>
#include <algorithm>
#include "./Headers/structures.h"

void reInsertion(reOptimization &bestNeighbour, vector<vector<Subseq>> subseqInfo, Solution &solution, double **matrizAdj) {

    int bestI, bestJ, lastSwitchablevertex = solution.circuit.size() - 2;
    double cost, bestCost = __DBL_MAX__;
    vector<int> circuit = solution.circuit;

    for(int i = 1; i < lastSwitchablevertex-1; i++) {
        for(int j = i + 2; j <= lastSwitchablevertex; j++) {
            
            cost = subseqInfo[DEPOT][i-1].cost
                    +subseqInfo[i+1][j].width * (subseqInfo[DEPOT][i-1].time
                                                    +matrizAdj[circuit[i-1]][circuit[i+1]])
                    +subseqInfo[i+1][j].cost
                    +(subseqInfo[DEPOT][i-1].time
                        +matrizAdj[circuit[i-1]][circuit[i+1]]
                        +subseqInfo[i+1][j].time
                        +matrizAdj[circuit[j]][circuit[i]])
                    +subseqInfo[j+1][lastSwitchablevertex+1].width * (subseqInfo[0][i-1].time
                                                                        +matrizAdj[circuit[i-1]][circuit[i+1]]
                                                                        +subseqInfo[i+1][j].time
                                                                        +matrizAdj[circuit[j]][circuit[i]]
                                                                        +matrizAdj[circuit[i]][circuit[j+1]])
                    +subseqInfo[j+1][lastSwitchablevertex+1].cost
                    ;            

            if(cost < bestCost) {
                bestI = i;
                bestJ = j;
                bestCost = cost;
            }
        }
    }
    
    for(int i = 5; i <= lastSwitchablevertex; i++) {
        for(int j = i - 4; j > DEPOT; j--) {
            
            cost = subseqInfo[DEPOT][j-1].cost
                    +subseqInfo[DEPOT][j-1].time + matrizAdj[circuit[j-1]][circuit[i]]
                    +subseqInfo[j][i-1].width * (subseqInfo[DEPOT][j-1].time
                                                    +matrizAdj[circuit[j-1]][circuit[i]]
                                                    +matrizAdj[circuit[i]][circuit[j]])
                    +subseqInfo[j][i-1].cost
                    +subseqInfo[i+1][lastSwitchablevertex+1].width * (subseqInfo[DEPOT][j-1].time
                                                                        +matrizAdj[circuit[j-1]][circuit[i]]
                                                                        +matrizAdj[circuit[i]][circuit[j]]
                                                                        +subseqInfo[j][i-1].time
                                                                        +matrizAdj[circuit[i-1]][circuit[i+1]])
                    +subseqInfo[i+1][lastSwitchablevertex+1].cost
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