#include "graph_gen.h"
#include "algorithms.h"

#include <random>
#include <iostream>

using namespace std;

// Generates a complete graph with "V" vertices with random egde weights.
vector<vector<int>> make_random_graph(int seed, int V, 
	int min_edge_weight, int max_edge_weight) {
	default_random_engine re(seed);
	uniform_int_distribution<int> id(min_edge_weight, max_edge_weight);
	vector<vector<int>> adj_mat(V, vector<int>(V, INF));
	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j)
			if (i == j)
				adj_mat[i][j] = 0;
			else
				adj_mat[i][j] = id(re);
	auto tmp_adj_mat = adj_mat;
	floyd_warshall(tmp_adj_mat);
	for (int i = 0; i < V; ++i)
		if (tmp_adj_mat[i][i] < 0) {
			cerr << "Accidentally generated a graph with a negative weight cycle, trying again... " << endl;
			return make_random_graph(seed+1, V, min_edge_weight, max_edge_weight);

		}
	return adj_mat;
}