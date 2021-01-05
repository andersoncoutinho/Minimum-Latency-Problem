#include <vector>
#include <chrono>
#include "structures.h"

using namespace std;

extern bool Compare(InsertionInfo v1, InsertionInfo v2);
extern void construction(Solution &, int, double **);
extern void gils(Solution &, int, int, int, double **);
extern void fillNeighbourhoods(vector<int> &);
extern void fillSubseqInfo(vector<int> &, double **, vector<vector<Subseq>> &, int);
extern void hSwap(reOptimization &, vector<vector<Subseq>>, Solution &, double **);
extern void opt2(reOptimization &, vector<vector<Subseq>>, Solution &, double **);
extern void orOpt2(reOptimization &, vector<vector<Subseq>>, Solution &, double **);
extern void orOpt3(reOptimization &, vector<vector<Subseq>>, Solution &, double **);
extern void perturb(vector<int> &, int, double **);
extern void printSolution(Solution , chrono::duration<double>);
extern void reInsertion(reOptimization &, vector<vector<Subseq>>, Solution &, double **);
extern void rvnd(Solution &, vector<vector<Subseq>> &, double **);
