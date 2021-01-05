#include <vector>
using namespace std;

#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED
struct Solution {
  vector<int> circuit;
  double latency;
};
#endif 

#ifndef INSERTIONINFO_H_INCLUDED
#define INSERTIONINFO_H_INCLUDED
struct InsertionInfo {
    int insertedVertex;
    double cost;
};
#endif 

#ifndef SUBSEQ_H_INCLUDED
#define SUBSEQ_H_INCLUDED
struct Subseq {
    double time;
    double cost;
    double width;
};
#endif 

#ifndef REOPTIMIZATION_H_INCLUDED
#define REOPTIMIZATION_H_INCLUDED
struct reOptimization {
    double cost;
    int firstvertex;
    int secondvertex;
};
#endif


