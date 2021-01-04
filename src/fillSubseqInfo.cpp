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

    for(int i = firstVertex; i <= lastVertex; i++) {        
        subseqInfo[i][i].time = subseqInfo[i][i].cost = 0;
        subseqInfo[i][i].width = 1;
    }
    subseqInfo[DEPOT][DEPOT].width = 0;

    for(int i = DEPOT; i < firstVertex; i++) {
        for(int j = firstVertex; j <= lastVertex; j++) {

            subseqInfo[i][j].width = subseqInfo[i][j-1].width + subseqInfo[j][j].width;
            subseqInfo[i][j].time = subseqInfo[i][j-1].time + matrizAdj[solution[j-1]][solution[j]];
            subseqInfo[i][j].cost = subseqInfo[i][j-1].cost + subseqInfo[i][j].time;

            subseqInfo[j][i].width = subseqInfo[i][j].width;
            subseqInfo[j][i].time = subseqInfo[i][j].time;
        }
    }

    for(int i = firstVertex; i < lastVertex; i++) {
        for(int j = i+1; j <= lastVertex; j++) {

            subseqInfo[i][j].width = subseqInfo[i][j-1].width + subseqInfo[j][j].width;
            subseqInfo[i][j].time = subseqInfo[i][j-1].time + matrizAdj[solution[j-1]][solution[j]];
            subseqInfo[i][j].cost = subseqInfo[i][j-1].cost + subseqInfo[i][j].time;

            subseqInfo[j][i].width = subseqInfo[i][j].width;
            subseqInfo[j][i].time = subseqInfo[i][j].time;

        }
    }

    for(int i = lastVertex; i >= firstVertex; i--) {
        for(int j = i-1; j >= DEPOT; j--) {
            subseqInfo[i][j].cost = subseqInfo[i][j+1].cost + subseqInfo[i][j].time;
        }
    } 
}