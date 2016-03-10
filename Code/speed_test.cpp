// This file implements a very basic test of execution time.
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

#include "algorithms.h"
#include "graph_gen.h"

using namespace std;

// Don't use negative weight edges to avoid
// generation of graphs with negative cycles.
// This allows the test to run quickly and not spend
// much time generating graphs.
const int MIN_EDGE_COST = 1, MAX_EDGE_COST = 100;
// The density of edges in test graphs.
const double DENSITY = 0.75;

// Tests for correctness using a particular RNG "seed",
// on graphs with "V" vertices.
void run_test(int seed, int V) {
	// Create the graph.
	vector<vector<int>> adj_mat = 
		make_random_graph(seed, V, MIN_EDGE_COST, MAX_EDGE_COST);
	// Generate a set of choices by removal of edges from the graph.
	// Removal chance conforms to graph density.
	vector<Edge> choices;
	default_random_engine re(seed);
	uniform_real_distribution<double> rd(0.0, 1.0);
	uniform_int_distribution<int> id(0, V - 1);
	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j)
			if (i != j && rd(re) >= DENSITY) {
				choices.push_back(Edge(i, j, adj_mat[i][j]));
				adj_mat[i][j] = INF;
			}
	// Dummy edge that represents taking no edge.
	choices.push_back(Edge(0, 0, 0));

	cout << "Ward-Datta (ms)\tBrute force (ms)" << endl;

	auto start = chrono::system_clock::now();
	ward_datta(adj_mat, choices);
	auto end = chrono::system_clock::now();
	cout << chrono::duration<double, milli>(end - start).count() << "\t";
	start = chrono::system_clock::now();
	brute_force(adj_mat, choices);
	end = chrono::system_clock::now();
	cout << chrono::duration<double, milli>(end - start).count() << endl;
}

int main() {
	int seed, v;
	cout << "The program uses a graph density of " << DENSITY << " but requires the user to provide a seed and the number of vertices" << endl;
	cout << "RNG seed: ";
	cin >> seed;
	cout << endl;
	cout << "Number of vertices: ";
	cin >> v;
	cout << endl;
	run_test(seed, v);
	return 0;
}
