#include "reduction.hpp"

using namespace std;

void sat2indset(int n, const vector<vector<int> > &cnf, graph &g){
	g = graph(2*n);
	for(int i = 0; i < n; i++){ // variable gadget
		g[i].push_back(n+i);
		g[n+i].push_back(i);
	}
	int v = 2*n; // # of verteces
	for(int i = 0; i < cnf.size(); i++){
		for(int j = 0; j < cnf[i].size(); j++){
			int x = cnf[i][j];
			x = (x > 0 ? x-1 : n-x-1);
			g.push_back(vertex());
			// edge between variable gadget and CNF gadget
			g[x].push_back(v+j);
			g[v+j].push_back(x);
			for(int k = 0; k < j; k++){ // CNF gadget
				g[v+j].push_back(v+k);
				g[v+k].push_back(v+j);
			}
		}
	}
}

void indset2maxcut(const graph &g, wgraph &g2){
	int n = g.size();
	int n2 = n+1;
	g2 = wgraph(n2);
	for(int i = 0; i < n; i++){
		if(g[i].size() != 2){
			g2[i].push_back((edge){2-g[i].size(), n});
			g2[n].push_back((edge){2-g[i].size(), i});
		}
		for(int j = 0; j < g[i].size(); j++){
			g2[i].push_back((edge){1, g[i][j]});
		}
	}
}

void maxcut2isingModel(const wgraph &g, igraph &g2){
	int n = g.size();
	g2 = igraph(n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < g[i].size(); j++){
			g2[i].push_back((iedge){g[i][j].cst/2.0, g[i][j].dst});
		}
	}
}

