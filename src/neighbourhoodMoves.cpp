#include <iostream>
#include <algorithm>
#include "./Headers/structures.h"

void opt2Move(Solution &solution, reOptimization &bestNeighbour) {
    reverse(solution.circuit.begin() + bestNeighbour.firstvertex, 
            solution.circuit.begin() + bestNeighbour.secondvertex+1);

    solution.latency = bestNeighbour.cost;
}

void hSwapMove(Solution &solution, reOptimization &bestNeighbour) {
    
    int aux = solution.circuit[bestNeighbour.firstvertex];
    
    solution.circuit[bestNeighbour.firstvertex] = solution.circuit[bestNeighbour.secondvertex];
    solution.circuit[bestNeighbour.secondvertex] = aux;    

    solution.latency = bestNeighbour.cost;
}

void reInsertionMove(Solution &solution, reOptimization &bestNeighbour) {
    
    int aux = solution.circuit[bestNeighbour.firstvertex];

    solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);        
    solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex, aux);

    solution.latency = bestNeighbour.cost;
}

void orOpt2Move(Solution &solution, reOptimization &bestNeighbour) {
    if(bestNeighbour.firstvertex > bestNeighbour.secondvertex) {

        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex,
                                solution.circuit[bestNeighbour.firstvertex+1]);
        
        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex,
                                solution.circuit[bestNeighbour.firstvertex+1]);

        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex+2);
        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex+2);
        
        
    } else {
        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex+1, 
                                    solution.circuit.begin() +  bestNeighbour.firstvertex,
                                    solution.circuit.begin() +  bestNeighbour.firstvertex+2);
                                
        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);
        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);
    }
    
    solution.latency = bestNeighbour.cost;

}

void orOpt3Move(Solution &solution, reOptimization &bestNeighbour) {

    if(bestNeighbour.firstvertex > bestNeighbour.secondvertex) {  
                            
        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex,
                                solution.circuit[bestNeighbour.firstvertex+2]);
        
        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex,
                                solution.circuit[bestNeighbour.firstvertex+2]);
        
        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex,
                                solution.circuit[bestNeighbour.firstvertex+2]);
        
        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex+3);
        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex+3);
        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex+3);

    } else {
        solution.circuit.insert(solution.circuit.begin()+bestNeighbour.secondvertex+1, 
                                    solution.circuit.begin() +  bestNeighbour.firstvertex,
                                    solution.circuit.begin() +  bestNeighbour.firstvertex+3);
                                           
        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);
        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);
        solution.circuit.erase(solution.circuit.begin() + bestNeighbour.firstvertex);
    }

    solution.latency = bestNeighbour.cost;

}