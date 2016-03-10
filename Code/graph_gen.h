#ifndef _GRAPH_GEN_H
#define _GRAPH_GEN_H

#include <vector>

// Generates a complete graph with "V" vertices with random egde weights.
std::vector<std::vector<int>> make_random_graph(int seed, int V, 
	int min_edge_weight, int max_edge_weight);

#endif