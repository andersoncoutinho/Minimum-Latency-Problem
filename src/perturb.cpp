#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Solution {
    vector<int> circuit;
    double latency;
};

int perturb(Solution &solution, int dimension, double **matrizAdj) {
	
	double cost;
	int positions[4];
    vector<int> circuit = solution.circuit;
	
	for(int i = 0; i < 4; i++) {
		positions[i] = rand() % (dimension-4)+1;
	}

	sort(positions, positions+4);

	for(int i = 0; i < 3; i++) {
		if(positions[i+1] <= positions[i]) {
			positions[i+1] = positions[i]+1;
		}
	}

	if(positions[1] - positions[0] > dimension/10) {
		positions[1] = positions[0] + dimension/10;
	}

	if(positions[3] - positions[2] > dimension/10) {
		positions[3] = positions[2] + dimension/10;
	}
	

	int firstRange = positions[1] - positions[0] + 1;
	int secondRange = positions[3] - positions[2] + 1; 		

	for(int i = 0; i < firstRange; i++) {
		circuit.insert(circuit.begin() + positions[2], circuit[positions[0]]);
		circuit.erase(circuit.begin() + positions[0]);
	}
	
	for(int i = 0; i < secondRange; i++) {
		circuit.insert(circuit.begin() + positions[0], circuit[positions[3]]);
		circuit.erase(circuit.begin() + positions[3]+1);
	}	

    solution.circuit = circuit;

    return positions[0];
}