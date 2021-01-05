#include <iostream>
#include <chrono>
#include "./Headers/structures.h"

void printSolution(Solution solution, chrono::duration<double> executionTime) {
  
  for(auto vertex : solution.circuit) {
    cout << vertex << ' ';
  }
  cout << endl;
  
  printf("Cost: %.0lf\n", solution.latency);
  cout << "Time: " << executionTime.count() << endl; 
}