#include <iostream>
#include <vector>

using namespace std;

struct Solution {
  vector<int> circuit;
  double latency;
};

extern void construction(Solution &solution, int dimension, double **matrizAdj);
extern void rvnd(Solution &solution, double **matrizAdj);
extern void perturb(Solution &solution, const Solution preSolution, double **matrizAdj);

void gils(Solution &bestSolution, int maxInteractions, int maxILS, int dimension, double **matrizAdj) {

    bestSolution.latency = __DBL_MAX__;

    for(int i = 0; i < maxInteractions; i++) {
        Solution preSolution, posSolution;

        construction(preSolution, dimension, matrizAdj);
        posSolution = preSolution;
        
        
        for(int iterIls = 0; i < maxILS; iterIls++) {

            rvnd(posSolution, matrizAdj);

            if(posSolution.latency < preSolution.latency) {
                preSolution = posSolution;
                iterIls = -1;
            }

            perturb(posSolution, preSolution, matrizAdj);
        }

        if(preSolution.latency < bestSolution.latency) {
            bestSolution = preSolution;
        }
    }    
}