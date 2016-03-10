// This file contains a simple correctness test.
// It generates random graphs and tests if the algorithms
// produce the same output.
#include <iostream>
#include <random>
#include <vector>

#include "algorithms.h"
#include "graph_gen.h"

using namespace std;

const int MIN_EDGE_COST = -2, MAX_EDGE_COST = 150;
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

	int bf_ans = brute_force(adj_mat, choices);
	int wd_ans = ward_datta(adj_mat, choices);

	if (bf_ans != wd_ans) {
		cout << "Test failed, debug output following..." << endl;
		cout << bf_ans << " " << wd_ans << endl;
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j)
				cout << adj_mat[i][j] << "\t";
			cout << endl;
		}
		for (auto e : choices) {
			cout << e.i << " " << e.j << " " << e.cost << endl;
		}
	} else {
		cout << "Test passed." << endl;
	}
}

int main() {
	int seed, v;
	cout << "The program uses a graph density of " << DENSITY << " but requires the user to provide a seed and the number of vertices" << endl;
	cout << "It is important to note that large (> 50 vertices) graphs have a high probability of having negative cycles, so be careful." << endl;
	cout << "If you wish to try larger graphs, we recommend adjusting the MIN_EDGE_COST and MAX_EDGE_COST constants and recompiling." << endl;
	cout << "RNG seed: ";
	cin >> seed;
	cout << "Number of vertices: ";
	cin >> v;
	run_test(seed, v);
	return 0;
}
