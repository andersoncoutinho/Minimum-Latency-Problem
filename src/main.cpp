#include <iostream>
#include "../Headers/readData.h"
#include "../Headers/functions.h"

#define MAX_INTERACTIONS 10 
#define MAX_ILS ((dimension > 100) ? dimension : 100)

double **matrizAdj;
int dimension;

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


