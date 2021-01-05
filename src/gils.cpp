#include <iostream>
#include <vector>
#include "../Headers/functions.h"


#define DEPOT 0

void gils(Solution &bestSolution, int maxIteractions, int maxILS, int dimension, double **matrizAdj) {
        
    bestSolution.latency = __DBL_MAX__;
    vector<vector<Subseq>> subseqInfo(dimension+1, vector<Subseq>(dimension+1));

    for(int i = 0; i < maxIteractions; i++) {
        Solution preSolution, posSolution;
        
        construction(preSolution, dimension, matrizAdj);
        fillSubseqInfo(preSolution.circuit, matrizAdj, subseqInfo, DEPOT);
        preSolution.latency = subseqInfo[DEPOT][dimension].cost;
        
        posSolution = preSolution;
        
        for(int iterIls = 0; iterIls < maxILS; iterIls++) {

            rvnd(posSolution, subseqInfo, matrizAdj);

            if(posSolution.latency < preSolution.latency) {
                preSolution = posSolution;
                iterIls = -1;
            } else {
                posSolution = preSolution;
            }

            perturb(posSolution.circuit, dimension, matrizAdj);
            fillSubseqInfo(posSolution.circuit, matrizAdj, subseqInfo, DEPOT);
            posSolution.latency = subseqInfo[DEPOT][dimension].cost;
        }

        if(preSolution.latency < bestSolution.latency) {
            bestSolution = preSolution;
        }
    }  
}