#include <iostream>
#include <random>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <chrono>

using namespace std;

const int INF = 1 << 29;

struct Edge {
	int i, j, cost;
	Edge(int i, int j, int cost) : i(i), j(j), cost(cost) {};
};

int sum_shortest(vector<vector<int> > adj_mat) {
	int V = adj_mat.size();
	// All pairs shortest path.
	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				adj_mat[i][j] = min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);
	// Sum up all shortest paths.
	int sum = 0;
	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j)
			if (adj_mat[i][j] != INF)
				sum += adj_mat[i][j];
	return sum;
}

int brute_force(vector<vector<int> > adj_mat, const vector<Edge>& el) {
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

int wardDatta(vector<vector<int> > adj_mat, const vector<Edge>& el) {
	int V = adj_mat.size();
	// Compute all shortest paths.
	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				adj_mat[i][j] = min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);
 	int best = INF;
	// Try every new edge.
	for (const Edge& e : el) {
		int sum = 0;
		// Sum up all shortest paths.
		// Does a single edge relaxation to see if the shortest path changed.
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				sum += min(adj_mat[i][j], adj_mat[i][e.i] + e.cost + adj_mat[e.j][j]);
		best = min(best, sum);
	}
	return best;
}

vector<vector<int> > make_random_graph(int seed, int V, double density) {
	default_random_engine re(seed);
	uniform_real_distribution<double> rd(0.0, 1.0);
	uniform_int_distribution<int> id(0, V*2);
	vector<vector<int> > adj_mat(V, vector<int>(V, INF));
	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j)
			if (i == j)
				adj_mat[i][j] = 0;
			else if (rd(re) <= density)
				adj_mat[i][j] = id(re);
	return adj_mat;
}

void run_test(int seed, int V, double density) {
	// Create the graph.
	vector<vector<int> > adj_mat = make_random_graph(seed, V, density);
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
	//cout << brute_force(adj_mat, choices) << endl;
	brute_force(adj_mat, choices);
	auto end = chrono::system_clock::now();
	cout << chrono::duration<double, milli>(end - start).count() << "ms" << endl;
	//cout << chrono::duration<double, milli>(end - start).count() << "\t";
	//cout << "TOO LONG" << '\t';
	//start = chrono::system_clock::now();
	//cout << wardDatta(adj_mat, choices) << endl;
	//wardDatta(adj_mat, choices);
	//end = chrono::system_clock::now();
	//cout << chrono::duration<double, milli>(end - start).count() << "ms" << endl;
	//cout << chrono::duration<double, milli>(end - start).count() << endl;
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
	for (int v = 100; v <= 1000; v += 100) {
		cout << v << "\t";
		run_test(100, v, 0.6);
	}
	//run_test(100, 1000, 0.6);

	return 0;
}
