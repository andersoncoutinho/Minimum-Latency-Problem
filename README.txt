This is a metaheuristic algorithm implemented in C++ for the Minimum Latency Problem(MLP).

MLP instances are inside the "instances" folder.

The "mlp" file solves a single MLP instance. To use it you need to open the terminal and type the following command line:

./mlp instances/"name of the instance file you want to solve"

The "run.sh" runs each instance file 10 times and prints the results in a txt file named "bm.txt" inside the "benchmark" folder.
To run it you need to open the terminal and type the following command line:

./run.sh

Inside the benchmark folder there's a "bmMean" executable that calculates the mean time and mean cost
of the values in the "bm.txt" file and prints them in a txt file named "bm_final.txt".
To run it you need to open the terminal and type the following command line:

./bm.exe

Reference

Silva, M. M.; Subramanian, A.; Vidal, T.; Ochi, L. S. A simple and effective metaheuristic for the Minimum Latency Problem. European Journal of Operational Research, 221, p. 513-520, 2012.