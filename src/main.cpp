#include "readData.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>

#define MAX_INTERACTIONS 10 
#define MAX_ILS ((dimension > 100) ? dimension : 100)

using namespace std;

struct Solution {
  vector<int> circuit;
  double latency;
};

double **matrizAdj;
int dimension;

extern void gils(Solution &, int, int, int, double **);
void printSolution(Solution , chrono::duration<double>);
void printTempo(vector<int> , double **);

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

void printSolution(Solution solution, chrono::duration<double> executionTime) {
  
  for(auto vertex : solution.circuit) {
    cout << vertex << ' ';
  }
  cout << endl;
  
  printf("Cost: %.0lf\n", solution.latency);
  //cout << "Cost: " << solution.latency << endl;
  cout << "Time: " << executionTime.count() << endl; 
}

void printTempo(vector<int> solution, double **matrizAdj) {
  
  int tamanho = dimension;
  double tempo = 0;

  for(int i = 0; i < dimension; i++, tamanho--) {
    tempo += (tamanho * matrizAdj[solution[i]][solution[i+1]]);
  }

  printf("Tempo: %.0lf\n", tempo);
  //cout << "tempo: " << tempo << endl;
}
