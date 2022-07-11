#include <iostream>
#include <vector>
#include <string>
#include "Grafo.h"

using namespace std;

void parsearDatos(vector<int>& data) {
	
	string s;
	cin >> s;

	while (s != "") {
		data.push_back(stoi(s));
		s = "";
		cin >> s;
	}
}

int main() {

	vector<int> data;
	parsearDatos(data);

	Grafo G (data);
	G.Johnson();

	return 0;
}
