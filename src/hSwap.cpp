#include <iostream>
#include <vector>
#include <algorithm>
#include "./Headers/structures.h"

void hSwap(reOptimization &bestNeighbour, vector<vector<Subseq>> subseqInfo, Solution &solution, double **matrizAdj) {

    int bestI, bestJ, lastSwitchablevertex = solution.circuit.size()-2;
    double cost, bestCost = __DBL_MAX__;
    vector<int> circuit = solution.circuit;

    for(int i = 1; i < lastSwitchablevertex; i++) {
        for(int j = i + 1; j <= lastSwitchablevertex; j++) {          

            if(j == i + 1) {

                cost =  subseqInfo[DEPOT][i-1].cost
                          +subseqInfo[j][i].width * (subseqInfo[DEPOT][i-1].time + matrizAdj[circuit[i-1]][circuit[j]])
                          +subseqInfo[j][i].cost
                          +subseqInfo[j+1][lastSwitchablevertex+1].width * (subseqInfo[DEPOT][i-1].time
                                                                            +matrizAdj[circuit[i-1]][circuit[j]]
                                                                            +subseqInfo[j][i].time
                                                                            +matrizAdj[circuit[i]][circuit[j+1]])
                          +subseqInfo[j+1][lastSwitchablevertex+1].cost
                        ;


            } else {
            
                cost = subseqInfo[DEPOT][i-1].cost
                        +subseqInfo[DEPOT][i-1].time + matrizAdj[circuit[i-1]][circuit[j]]
                        +subseqInfo[i+1][j-1].width * (subseqInfo[DEPOT][i-1].time
                                                        +matrizAdj[circuit[i-1]][circuit[j]]
                                                        +matrizAdj[circuit[j]][circuit[i+1]])
                        +subseqInfo[i+1][j-1].cost
                        +subseqInfo[DEPOT][i-1].time
                            +matrizAdj[circuit[i-1]][circuit[j]]
                            +matrizAdj[circuit[j]][circuit[i+1]]
                            +subseqInfo[i+1][j-1].time
                            +matrizAdj[circuit[j-1]][circuit[i]]
                            
                        +subseqInfo[j+1][lastSwitchablevertex+1].width * (+subseqInfo[DEPOT][i-1].time
                                                                            +matrizAdj[circuit[i-1]][circuit[j]]
                                                                            +matrizAdj[circuit[j]][circuit[i+1]]
                                                                            +subseqInfo[i+1][j-1].time
                                                                            +matrizAdj[circuit[j-1]][circuit[i]]
                                                                            +matrizAdj[circuit[i]][circuit[j+1]])
                        +subseqInfo[j+1][lastSwitchablevertex+1].cost
                        ;

            }

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