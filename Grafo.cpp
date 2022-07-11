#include <vector>
#include <queue>
#include <iostream>
#include "Grafo.h"

#define INF INT_MAX
#define NIL -1
#define edge pair<int, int>
#define matrix vector<vector<int>>

using namespace std;

Grafo::Grafo(vector<int> data) {
	
	V = data[0];
	int m = data[1];

	for (int i = 0; i < m; i++) {
		E.push_back(make_pair(data[2 + 3 * i], data[3 + 3 * i]));
		W.push_back(data[4 + 3 * i]);
	}

	generarMAT();
}

Grafo::Grafo(int V, vector<edge> E, vector<int> W) {

	this->V = V;
	this->E = E;
	this->W = W;

	generarMAT();
}

void Grafo::generarMAT() {
	
	for (int i = 0; i < V; i++) {

		vector<int> v(V, INF);
		MAT.push_back(v);
	}

	int w = 0;
	for (edge e : E) {
		MAT[e.first][e.second] = W[w];
		w++;
	}
}

bool Grafo::relax(vector<int>& d, vector<int>& pi, edge e) {
	
	int u = e.first;
	int v = e.second;

	if (d[u] != INF && d[v] > d[u] + MAT[u][v]) { 

		d[v] = d[u] + MAT[u][v];
		pi[v] = u;

		return true;
	}

	return false;
}

bool Grafo::BellmanFord(vector<int>& d, vector<int>& pi, int s){

	d = vector<int>(V, INF);
	pi = vector<int>(V, NIL);
	d[s] = 0;

	for (int i = 0; i < V; i++) {
		for (edge e : E) { 
			relax(d, pi, e); 
		}
	}

	for (edge e : E) { 
		if (relax(d, pi, e)) return false; 
	}

	return true;
}

void Grafo::Dijkstra(vector<int>& d, vector<int>& pi, int s) {
	
	if (d.size() == 0) d = vector<int>(V, INF);
	if (pi.size() == 0) pi = vector<int>(V, NIL);
	d[s] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;

	Q.push({0, s});
	
	while (!Q.empty()) {
		
		int u = Q.top().second;
		int du = Q.top().first;
		Q.pop();

		if (du != d[u]) continue;

		for (int v = 0; v < V; v++) {
			if (MAT[u][v] != INF) { // <------------------------------------------------------- ACA ojo
				if (relax(d, pi, {u,v})) Q.push({d[v], v});
			}
		}
	}
}

 matrix Grafo::Johnson() {
	
	vector<edge> E2 = E;
	vector<int> W2 = W;

	int s = V;
	for (int v = 0; v < V; v++) { 
		E2.push_back(make_pair(s, v)); 
		W2.push_back(0);
	}

	Grafo G2 (V + 1, E2, W2);

	vector<int> d;
	vector<int> pi;

	if (G2.BellmanFord(d, pi, s)) {

		for (edge e : G2.E) { // <--------------------------- ARREGLAR

			int u = e.first;
			int v = e.second;

			G2.MAT[u][v] = G2.MAT[u][v] + d[u] - d[v];
		}

		matrix D (V, vector<int>(V, INF));
		
		for (int v = 0; v < V; v++) { 
			G2.Dijkstra(D[v], pi, v);
		}

		cout << "1" << endl;

		for (int u = 0; u < V; u++) {
			for (int v = 0; v < V; v++) {

				D[u][v] = D[u][v] + d[v] - d[u];

				if (D[u][v] == INF) {
					cout << "INF "; 
				}else {
					cout << D[u][v] << " ";
				}
			}
			cout << endl;
		}

		return D;

	}else {
		cout << "0" << endl;
	}
}