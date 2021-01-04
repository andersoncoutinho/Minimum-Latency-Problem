#include <iostream>
#include <vector>

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

extern void construction(Solution &, int, double **);
extern void rvnd(Solution &, vector<vector<Subseq>> &, double **);
extern void fillSubseqInfo(vector<int> &, double **, vector<vector<Subseq>> &, int);
extern void perturb(Solution &, int, double **);

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

            perturb(posSolution, dimension, matrizAdj);
            fillSubseqInfo(posSolution.circuit, matrizAdj, subseqInfo, DEPOT);
            posSolution.latency = subseqInfo[DEPOT][dimension].cost;
        }

        if(preSolution.latency < bestSolution.latency) {
            bestSolution = preSolution;
        }
    }  
}