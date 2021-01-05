#include <vector>
#define DEPOT 0
using namespace std;

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED


struct Solution {
  vector<int> circuit;
  double latency;
};

struct InsertionInfo {
    int insertedVertex;
    double cost;
};

struct Subseq {
    double time;
    double cost;
    double width;
};

struct reOptimization {
    double cost;
    int firstvertex;
    int secondvertex;
};

#endif 



