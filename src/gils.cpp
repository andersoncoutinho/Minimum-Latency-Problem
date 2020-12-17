#include <iostream>
#include <vector>

using namespace std;

struct Solution {
  vector <int> circuit;
  double latency;
};

extern void construction(Solution &solution, double **matrizAdj, double alfa);
extern void rvnd(Solution &solution, double **matrizAdj);
extern void perturb(Solution &solution, const Solution preSolution, double **matrizAdj);

void gils(Solution &bestSolution, int maxInteractions, int maxILS, int dimension, double **matrizAdj) {

    bestSolution.latency = __DBL_MAX__;

    Solution preSolution, posSolution;

    for(size_t i = 0; i < maxInteractions; i++) {
        
        double alfa; // tem que ver como faz esse alfa, parece diferente do TSP. talvez possa ser
                 // colocado direto dentro da construção
        construction(preSolution, matrizAdj, alfa);
        posSolution = preSolution;

        for(size_t iterIls = 0; i < maxILS; iterIls++) {

            rvnd(posSolution, matrizAdj);

            if(posSolution.latency < preSolution.latency) {
                preSolution = posSolution;
                iterIls = -1;
            }

            perturb(posSolution, preSolution, matrizAdj);
        }
    }

    if(preSolution.latency < bestSolution.latency) {
        bestSolution = preSolution;
    }
    
}