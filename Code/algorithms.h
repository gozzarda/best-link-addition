#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

#include <vector>
#include <iterator>

// A reasonably large infinity value for 32-bit integers.
// We avoid INT_MAX to avoid overflows.
const int INF = 1e8;

// A weighted edge in a graph.
struct Edge {
	int i, j, cost;
	Edge(int i, int j, int cost) : i(i), j(j), cost(cost) {};
};

// A minimal implementation of the Floyd-Warshall algorithm.
// O(V^3).
// Takes an adjacency matrix as input and uses it 
// as the dynamic programming table directly.
void floyd_warshall(std::vector<std::vector<int>> &adj_mat);

// Computes the APSP table and returns the sum of all shortest paths.
int sum_shortest(std::vector<std::vector<int>> adj_mat);

// Implements the naive algorithm for finding a single edge
// from a set of edges "el" that, when added to a graph
// defined by "adj_mat", minimizes the average shortest path.
int brute_force(std::vector<std::vector<int>> adj_mat, const std::vector<Edge>& el);

// The less naive algorithm for finding a single edge
// from a set of edges "el" that, when added to a graph
// defined by "adj_mat", minimizes the average shortest path
int ward_datta(std::vector<std::vector<int>> adj_mat, const std::vector<Edge>& el);

// Experimenatl algorithm for finding a single edge
// from a set of edges "el" that, when added to a graph
// defined by "adj_mat", minimizes the average shortest path
int gozzard(std::vector<std::vector<int>> adj_mat, const std::vector<Edge>& el);

#endif