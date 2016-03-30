#include "algorithms.h"

#include <algorithm>

using namespace std;

// A minimal implementation of the Floyd-Warshall algorithm.
// O(V^3).
// Takes an adjacency matrix as input and uses it 
// as the dynamic programming table directly.
void floyd_warshall(vector<vector<int>> &adj_mat) {
	int V = adj_mat.size();
	// All pairs shortest path.
	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				adj_mat[i][j] = min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);
}

// Computes the APSP table and returns the sum of all shortest paths.
int sum_shortest(vector<vector<int>> adj_mat) {
	int V = adj_mat.size();
	// APSP.
	floyd_warshall(adj_mat);
	// Sum up all shortest paths.
	int sum = 0;
	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j) {
			sum += adj_mat[i][j];
			sum = min(sum, INF);
		}
	return sum;
}

// Implements the naive algorithm for finding a single edge
// from a set of edges "el" that, when added to a graph
// defined by "adj_mat", minimizes the average shortest path.
int brute_force(vector<vector<int>> adj_mat, const vector<Edge>& el) {
	int best = INF;
	// Try taking every edge.
	for (const Edge& e : el) {
		// Update graph and recompute and re-sum shortest paths.
		int old_c = adj_mat[e.i][e.j];
		adj_mat[e.i][e.j] = e.cost;
		best = min(best, sum_shortest(adj_mat));
		adj_mat[e.i][e.j] = old_c;

	}
	return best;
}

// The less naive algorithm for finding a single edge
// from a set of edges "el" that, when added to a graph
// defined by "adj_mat", minimizes the average shortest path
int ward_datta(vector<vector<int>> adj_mat, const vector<Edge>& el) {
	int V = adj_mat.size();
	// Compute all shortest paths.
	floyd_warshall(adj_mat);
 	int best = INF;
	// Try every new edge.
	for (const Edge& e : el) {
		int sum = 0;
		// Sum up all shortest paths.
		// Does a single edge relaxation to see if the shortest path changed.
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j) {
				sum += min(adj_mat[i][j], adj_mat[i][e.i] + e.cost + adj_mat[e.j][j]);
				sum = min(sum, INF);
			}
		best = min(best, sum);
	}
	return best;
}

// Experimenatl algorithm for finding a single edge
// from a set of edges "el" that, when added to a graph
// defined by "adj_mat", minimizes the average shortest path
int gozzard(std::vector<std::vector<int>> adj_mat, const std::vector<Edge>& el) {
	int V = adj_mat.size();
	int E = el.size();
	// Compute all shortest paths.
	floyd_warshall(adj_mat);
	int sum = 0;
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			sum += adj_mat[i][j];
		}
	}
 	// "Votes" for best new edge
 	std::vector<int> votes(E, 0);
 	for (int src = 0; src < V; ++src) {
 		// Build lists of threshold lengths from src to mid required to be new shortest path
 		std::vector<std::vector<int>> threshholds(V);
 		for (int dst = 0; dst < V; ++dst) {
 			for (int mid = 0; mid < V; ++mid) {
 				threshholds[mid].push_back(adj_mat[src][dst] - adj_mat[mid][dst]);
 			}
 		}
 		// Sort thresholds and compute sum arrays
 		std::vector<std::vector<int>> threshsums(V);
 		for (int i = 0; i < V; ++i) {
 			std::sort(threshholds[i].begin(), threshholds[i].end());
 			threshsums[i].push_back(0);
 			for (int elem : threshholds[i]) {
 				threshsums[i].push_back(threshsums[i].back() + elem);
 			}
 		}
 		// For each edge find what total length it reduces the sum of shortest paths starting at src by and add that to votes
 		for (int i = 0; i < E; ++i) {
 			Edge e = el[i];
 			int len = adj_mat[src][e.i] + e.cost;
 			auto it = std::lower_bound(threshholds[e.j].begin(), threshholds[e.j].end(), len);
 			int ind = std::distance(threshholds[e.j].begin(), it);
 			int num = std::distance(it, threshholds[e.j].end());
 			int vote = threshsums[e.j].back() - threshsums[e.j][ind] - num * len;
 			votes[i] += vote;
 		}
 	}
 	// Find edge with most votes
 	int best_edge = 0;
 	for (int i = 0; i < E; ++i) {
 		if (votes[i] > votes[best_edge]) {
 			best_edge = i;
 		}
 	}
 	// Compute and return new APSP length sum
 	if (votes[best_edge] > 0) {
 		sum -= votes[best_edge];
 	}
	return sum;
}