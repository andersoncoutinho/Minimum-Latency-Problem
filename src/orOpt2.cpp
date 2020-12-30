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

void orOpt2(reOptimization &bestNeighbour, vector<vector<Subseq>> subseqInfo, Solution &solution, double **matrizAdj) {

    int bestI, bestJ;
    double bestCost = __DBL_MAX__;
    vector<int> circuit = solution.circuit;
    int lastSwitchablevertex = solution.circuit.size()-2;

    double cost;

    for(int i = 1; i < lastSwitchablevertex - 2; i++) {

        for(int j = i + 2; j <= lastSwitchablevertex; j++) {
            
            cost = subseqInfo[DEPOT][i-1].cost
                    +subseqInfo[i+2][j].width * (subseqInfo[DEPOT][i-1].time
                                                    +matrizAdj[circuit[i-1]][circuit[i+2]])
                    +subseqInfo[i+2][j].cost
                    //arrumar esse número mágico
                    + 2 * (subseqInfo[0][i-1].time
                            +matrizAdj[circuit[i-1]][circuit[i+2]]
                            +subseqInfo[i+2][j].time
                            +matrizAdj[circuit[j]][circuit[i]])
                    +subseqInfo[i][i+1].cost
                    +subseqInfo[j+1][lastSwitchablevertex+1].width * (subseqInfo[0][i-1].time
                                                                        +matrizAdj[circuit[i-1]][circuit[i+2]]
                                                                        +subseqInfo[i+2][j].time
                                                                        +matrizAdj[circuit[j]][circuit[i]]
                                                                        +subseqInfo[i][i+1].time
                                                                        +matrizAdj[circuit[i+1]][circuit[j+1]])
                    +subseqInfo[j+1][lastSwitchablevertex+1].cost
                    ;
            
            if(cost < bestCost) {
                bestI = i;
                bestJ = j;
                bestCost = cost;
            }
        }
    }
    
    for(int i = 3; i < lastSwitchablevertex; i++) {

        for(int j = i - 1; j > 0; j--) {

            cost = subseqInfo[DEPOT][j-1].cost
                    + 2 * (subseqInfo[0][j-1].time
                            +matrizAdj[circuit[j-1]][circuit[i]])
                    +subseqInfo[i][i+1].cost
                    +subseqInfo[j][i+2].width * (subseqInfo[0][j-1].time
                                                    +matrizAdj[circuit[j-1]][circuit[i]]
                                                    +matrizAdj[circuit[i+1]][circuit[j]]
                                                    +subseqInfo[j][i+2].time)
                    +subseqInfo[j][i+2].cost
                    +subseqInfo[i+2][lastSwitchablevertex+1].width * (subseqInfo[0][j-1].time
                                                                        +matrizAdj[circuit[j-1]][circuit[i]]
                                                                        +matrizAdj[circuit[i+1]][circuit[j]]
                                                                        +subseqInfo[j][i+2].time
                                                                        +matrizAdj[circuit[i-1]][circuit[i+2]])
                    +subseqInfo[i+2][lastSwitchablevertex+1].cost

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