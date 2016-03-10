#include <iostream>
#include <random>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <chrono>

#include "algorithms.h"

using namespace std;

const int MIN_EDGE_WEIGHT = -3, MAX_EDGE_WEIGHT = 100;

vector<vector<int> > make_random_graph(int seed, int V, double density) {
	default_random_engine re(seed);
	uniform_real_distribution<double> rd(0.0, 1.0);
	uniform_int_distribution<int> id(MIN_EDGE_WEIGHT, MAX_EDGE_WEIGHT);
	vector<vector<int>> adj_mat(V, vector<int>(V, INF));
	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j)
			if (i == j)
				adj_mat[i][j] = 0;
			else if (rd(re) <= density)
				adj_mat[i][j] = id(re);
	auto tmp_adj_mat = adj_mat;
	floyd_warshall(tmp_adj_mat);
	for (int i = 0; i < V; ++i)
		if (tmp_adj_mat[i][i] < 0) {
			cerr << "Accidentally generated a graph with a negative weight cycle, trying again... " << endl;
			return make_random_graph(seed+1, V, density);

		}
	return adj_mat;
}

void run_test(int seed, int V, double density) {
	// Create the graph.
	vector<vector<int>> adj_mat = make_random_graph(seed, V, density);
	// Generate the choices of new edges to add.
	vector<Edge> choices;
	default_random_engine re(seed);
	uniform_int_distribution<int> id(0, V - 1);
	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j)
			if (adj_mat[i][j] == INF && i != j)
				choices.push_back(Edge(i, j, id(re)));
	// Dummy edge that represents taking no edge.
	choices.push_back(Edge(0, 0, 0));

	// Run benchmarks.
	auto start = chrono::system_clock::now();
	cout << brute_force(adj_mat, choices) << endl;
	auto end = chrono::system_clock::now();
	cout << chrono::duration<double, milli>(end - start).count() << "\t";
	//cout << "TOO LONG" << '\t';
	start = chrono::system_clock::now();
	cout << ward_datta(adj_mat, choices) << endl;
	end = chrono::system_clock::now();
	cout << chrono::duration<double, milli>(end - start).count() << endl;
}

int main() {
	/*int seed, V;
	double density;
	// Get test run variables.
	cout << "Enter Seed: ";
	cin >> seed;
	cout << "Enter V: ";
	cin >> V;
	cout << "Enter Density (0.0, 1.0): ";
	cin >> density;

	run_test(seed, V, density);*/
	for (int v = 10; v <= 50; v += 1) {
		cout << v << endl;
		run_test(100, v, 0.6);
	}
	//run_test(100, 1000, 0.6);

	return 0;
}
