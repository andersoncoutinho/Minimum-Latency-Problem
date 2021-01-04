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

void fillSubseqInfo(vector<int> &solution, double **matrizAdj, vector<vector<Subseq>> &subseqInfo, int firstVertex) {

    int lastVertex = solution.size() - 1;
    double time, cost, width;

    for(int i = firstVertex; i < lastVertex; i++) {        
        subseqInfo[i][i].time = subseqInfo[i][i].cost = 0;
        subseqInfo[i][i].width = 1;
    }
    subseqInfo[DEPOT][DEPOT].width = 0;
    
}