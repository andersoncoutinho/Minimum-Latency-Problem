#include "readData.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

struct Solution {
  vector <int> circuit;
  double latency;
};

double ** matrizAdj; // matriz de adjacencia
int dimension; // quantidade total de vertices

extern void gils(Solution &solution, int dimension, double **matrizAdj);
void printSolution(Solution solution, chrono::duration<double> executionTime);
void printData();

int main(int argc, char** argv) {
  
  srand(time(NULL));
  readData(argc, argv, &dimension, &matrizAdj);

  auto begin = chrono::system_clock::now();

  Solution solution;
  gils(solution, dimension, matrizAdj);
  auto end = chrono::system_clock::now();
  chrono::duration<double> executionTime = end - begin;

  printSolution(solution, executionTime);

  return 0;  

}

void printData() {
  cout << "dimension: " << dimension << endl;
  for (size_t i = 1; i <= dimension; i++) {
    for (size_t j = 1; j <= dimension; j++) {
      cout << matrizAdj[i][j] << " ";
    }
    cout << endl;
  }
}

void printSolution(Solution solution, chrono::duration<double> executionTime) {
  
  for(auto i : solution.circuit) {
    cout << solution.circuit[i] << ' ';
  }

  cout << endl;

  cout << "Cost: " << solution.latency << endl;
  cout << "Time: " << executionTime.count() << endl; 

}
