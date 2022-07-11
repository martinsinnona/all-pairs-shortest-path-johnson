#pragma once
#include <vector>

#define edge pair<int, int>
#define matrix vector<vector<int>>

using namespace std;

class Grafo {

	public:
		Grafo(vector<int> data);
		Grafo(int V, vector<edge> E, vector<int> W);

		bool BellmanFord(vector<int>& d, vector<int>& pi, int s);
		void Dijkstra(vector<int>& d, vector<int>& pi, int s);
		matrix Johnson();

	private:
		int V;
		vector<edge> E;
		vector<int> W;
		vector<vector<int>> MAT;

		void generarMAT();
		bool relax(vector<int>& d, vector<int>& pi, edge e);
};