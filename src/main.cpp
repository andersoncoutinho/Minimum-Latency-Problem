#include "readData.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>

#define MAX_INTERACTIONS 100 //revisar esse valor
#define MAX_ILS 2 //revisar esse valor

using namespace std;

struct Solution {
  vector<int> circuit;
  double latency;
};

double **matrizAdj; // matriz de adjacencia
int dimension; // quantidade total de vertices

extern void gils(Solution &solution, int maxInteractions, int maxILS, int dimension, double **matrizAdj);
void printSolution(Solution solution, chrono::duration<double> executionTime);
void printData();
void printTempo(vector<int> solution, double **matrizAdj);

int main(int argc, char **argv) {
  
  srand(time(NULL));
  readData(argc, argv, &dimension, &matrizAdj);

  auto begin = chrono::system_clock::now();

  Solution solution;
  gils(solution, MAX_INTERACTIONS, MAX_ILS, dimension, matrizAdj);
  auto end = chrono::system_clock::now();
  chrono::duration<double> executionTime = end - begin;
  

  printSolution(solution, executionTime);

  printTempo(solution.circuit, matrizAdj);

  return 0;  

}

void printData() {
  cout << "dimension: " << dimension << endl;
  for (int i = 1; i <= dimension; i++) {
    for (int j = 1; j <= dimension; j++) {
      cout << matrizAdj[i][j] << " ";
    }
    cout << endl;
  }
}

void printSolution(Solution solution, chrono::duration<double> executionTime) {
  
  for(auto vertex : solution.circuit) {
    cout << vertex << ' ';
  }

  cout << endl;

  cout << "Cost: " << solution.latency << endl;
  cout << "Time: " << executionTime.count() << endl; 

}

void printTempo(vector<int> solution, double **matrizAdj) {
  
  int tamanho = dimension;//solution.circuit.size()-1;
  double tempo = 0;
  for(int i = 0; i < dimension; i++, tamanho--) {
    tempo += (tamanho * matrizAdj[solution[i]][solution[i+1]]);
  }
  cout << "tempo: " << tempo << endl;
  getchar();

}
