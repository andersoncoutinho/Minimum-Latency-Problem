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

  return 0;  
}

void printSolution(Solution solution, chrono::duration<double> executionTime) {
  
  for(auto vertex : solution.circuit) {
    cout << vertex << ' ';
  }
  cout << endl;
  
  printf("Cost: %.0lf\n", solution.latency);
  cout << "Execution Time: " << executionTime.count() << endl; 
}
