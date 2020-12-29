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

void fillNeighbourhoods(vector<int> &);
void printTempo(vector<int> solution, double **matrizAdj);
extern void opt2(reOptimization &, vector<vector<Subseq>>, Solution &, double **);
extern void fillSubseqInfo(vector<vector<Subseq>> &subseqInfo, vector<int> &solution, int firstVertex, double **matrizAdj);

void rvnd(Solution &solution, vector<vector<Subseq>> &subseInfo, double **matrizAdj) {
    
    vector<int> neighbourhoods;
    fillNeighbourhoods(neighbourhoods);
    reOptimization bestNeighbour;
    int aux;

    while(!neighbourhoods.empty()) {

        bestNeighbour.cost = solution.latency;
        
        int neighbourhood = rand() % neighbourhoods.size();

        switch(neighbourhoods[neighbourhood]) {
            case 1:
                opt2(bestNeighbour, subseInfo, solution, matrizAdj);

                if(bestNeighbour.cost < solution.latency) {
                    reverse(solution.circuit.begin() + bestNeighbour.firstvertex, 
                            solution.circuit.begin() + bestNeighbour.secondvertex+1);

                    solution.latency = bestNeighbour.cost;

                    cout << "Latência: " << solution.latency << endl;
                    printTempo(solution.circuit, matrizAdj);

                    fillNeighbourhoods(neighbourhoods);
                    fillSubseqInfo(subseInfo, solution.circuit, DEPOT, matrizAdj);
                    
                    /*
                    double tempo = 0;
                    int dimension = solution.circuit.size() - 1;
                    int tamanho = dimension;
                    for(int i = 0; i < dimension; i++, tamanho--) {
                        tempo += (tamanho * matrizAdj[solution.circuit[i]][solution.circuit[i+1]]);
                    }
                    cout << tempo << endl;
                    */
                } else {

                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);

                }

                break;
            case 2:

                if(bestNeighbour.cost < solution.latency) {
                    

                } else {

                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);

                }

                break;

            case 3:

                if(bestNeighbour.cost < solution.latency) {
                    

                } else {

                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);

                }

                break;
            case 4:

                if(bestNeighbour.cost < solution.latency) {
                    

                } else {

                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);

                }

                break;
            case 5:

                if(bestNeighbour.cost < solution.latency) {
                    

                } else {

                    neighbourhoods.erase(neighbourhoods.begin() + neighbourhood);

                }

                break;
        }
    }
}

void fillNeighbourhoods(vector<int> &neighbourhoods) {
    neighbourhoods = {1, 2, 3, 4, 5};
}