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
extern void perturb(Solution &, const Solution, double **);
void fillSubseqInfo(vector<vector<Subseq>> &, vector<int> &, int, double **);

void gils(Solution &bestSolution, int maxInteractions, int maxILS, int dimension, double **matrizAdj) {
        
    bestSolution.latency = __DBL_MAX__;
    vector<vector<Subseq>> subseqInfo(dimension+1, vector<Subseq>(dimension+1));

    for(int i = 0; i < maxInteractions; i++) {
        Solution preSolution, posSolution;
        
        construction(preSolution, dimension, matrizAdj);
        fillSubseqInfo(subseqInfo, preSolution.circuit, DEPOT, matrizAdj);
        preSolution.latency = subseqInfo[DEPOT][dimension].cost;
        
        posSolution = preSolution;
        
        for(int iterIls = 0; iterIls < maxILS; iterIls++) {

            rvnd(posSolution, subseqInfo, matrizAdj);

            if(posSolution.latency < preSolution.latency) {
                preSolution = posSolution;
                iterIls = -1;
            }

           // perturb(posSolution, preSolution, matrizAdj);
        }

        if(preSolution.latency < bestSolution.latency) {
            bestSolution = preSolution;
        }
    }  
}

void fillSubseqInfo(vector<vector<Subseq>> &subseqInfo, vector<int> &solution, int firstVertex, double **matrizAdj) {
    
    int lastVertex = solution.size() - 1;
    double time, cost, width;

    for(int i = firstVertex; i <= lastVertex; i++) {
        for(int j = firstVertex; j <= lastVertex; j++) {
            
            time = cost = width = 0;

            if(i == j) {
                subseqInfo[i][j].time = 0;
                subseqInfo[i][j].cost = 0;

                if(i == 0 || i == lastVertex) {
                    subseqInfo[i][j].width = 0;
                } else {
                    subseqInfo[i][j].width = 1;
                }
            } else if(j > i) {

                if(i == 0 || j == lastVertex) {
                    width = j - i;
                    subseqInfo[i][j].width = width;
                } else {
                    width = j - i + 1;
                    subseqInfo[i][j].width = width;
                    width--;
                }
                for(int k = i; k < j; k++, width--) {
                    time += matrizAdj[solution[k]][solution[k+1]];
                    cost += (width * matrizAdj[solution[k]][solution[k+1]]);
                } 

            } else {

                if(j == 0 || i == lastVertex) {              
                    width = i - j;
                    subseqInfo[i][j].width = width;
                } else {
                    width = i - j + 1;
                    subseqInfo[i][j].width = width;
                    width--;
                }
                for(int k = i; k > j; k--, width--) {
                    time += matrizAdj[solution[k]][solution[k-1]];
                    cost += (width * matrizAdj[solution[k]][solution[k-1]]);
                }
            }
            subseqInfo[i][j].time = time;
            subseqInfo[i][j].cost = cost;
            
        }
    }
}