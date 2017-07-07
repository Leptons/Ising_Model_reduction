#include "io.hpp"
#include <iostream>
#include <sstream>

using namespace std;

void inputSat(int &n, vector<vector<int> > &cnf){ // assume SAT competition format
	string s;
	do {
		getline(cin, s);
	}while(s[0]=='c');
	stringstream ss(s);
	int m;
	string igns1, igns2; // ignore first strings
	ss >> igns1 >> igns2 >> n >> m; cin.ignore();
	cnf = vector<vector<int> >(m);
	for(int i = 0; i < m; i++){
		int x;
		while(cin >> x, x != 0){
			cnf[i].push_back(x);
		}
	}
}

void outputIndset(const graph &g){
	cout << g.size() << endl;
	for(int i = 0; i < g.size(); i++){
		cout << g[i].size() << " ";
		for(int j = 0; j < g[i].size(); j++){
			cout << g[i][j] << (j == g[i].size()-1 ? "\n" : " ");
		}
	}
}

void outputIsingModel(const igraph &g){
	int n = g.size();
	int m = 0;
	double offset = 0.0;
	for(int i = 0; i < n; i++) m += g[i].size();
	m /= 2;
	for(int i = 0; i < n; i++) for(int j = 0; j < g[i].size(); j++) offset += g[i][j].cst;
	offset /= 2.0;
	cout << n << " " << m << " " << offset << " is edges' sum" << endl;
	for(int i = 0; i < g.size(); i++){
		for(int j = 0; j < g[i].size(); j++){
			if(i < g[i][j].dst) cout << i+1 << " " << g[i][j].dst+1 << " " << g[i][j].cst << endl;
		}
	}
}
