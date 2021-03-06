#include "reduction.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

int getV(int n, int x){ return x > 0 ? x-1 : n-x-1; }
int sgn(int x){ return x == 0 ? 0 : (x > 0 ? 1 : -1); }

void rmSMEMaxcut(wgraph &g){
	for(int i = 0; i < g.size(); i++){
		sort(g[i].begin(), g[i].end(),
			[](const edge &a, const edge &b){ return a.dst < b.dst; });
		for(int j = g[i].size()-2; j >= 0; j--){
			if(g[i][j].dst == g[i][j+1].dst){
				g[i][j].cst += g[i][j+1].cst;
				g[i][j+1].cst = 0;
			}
		}
		for(int j = 0; j < g[i].size(); j++){
			if(i == g[i][j].dst) g[i][j].cst = 0;
		}
		g[i].erase(remove_if(g[i].begin(), g[i].end(), [](const edge &a){ return a.cst == 0;}), g[i].end());
	}
}

void sat_indset(int n, const vector<vector<int> > &cnf, graph &g){
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

void naesat3_maxcut(int n, const vector<vector<int> > &cnf, wgraph &g, bool maximize){
	g = wgraph(2*n);
	for(int i = 0; i < cnf.size(); i++){
		int x[3];
		for(int j = 0; j < 3; j++) x[j] = getV(n, cnf[i][j]);
		for(int j = 0; j < 3; j++){
			int j2 = (j+1)%3;
			g[x[j]].push_back((edge){1, x[j2]});
			g[x[j2]].push_back((edge){1, x[j]});
		}
	}
	int w = 1;
	if(maximize){
		for(int i = 0; i < n; i++){
			w = max(w, min<int>(g[i].size(), g[n+i].size())+1);
		}
	}
	for(int i = 0; i < n; i++){
		g[i].push_back((edge){w, n+i});
		g[n+i].push_back((edge){w, i});
	}
	rmSMEMaxcut(g);
}

void naesat3_maxcut2(int n, const vector<vector<int> > &cnf, wgraph &g, int &opt){
	g = wgraph(n);
	opt = cnf.size();
	for(int i = 0; i < cnf.size(); i++){
		int x[3];
		for(int j = 0; j < 3; j++) x[j] = abs(cnf[i][j])-1;
		for(int j = 0; j < 3; j++){
			int j2 = (j+1)%3;
			int ew = sgn(cnf[i][j])*sgn(cnf[i][j2]);
			g[x[j]].push_back((edge){ew, x[j2]});
			g[x[j2]].push_back((edge){ew, x[j]});
			opt += ew;
		}
	}
	opt /= 2;
	rmSMEMaxcut(g);
}

void sat_naesat(int n, const vector<vector<int> > &cnf, int &n2, vector<vector<int> > &cnf2){
	n2 = n+1;
	cnf2 = vector<vector<int> >(cnf);
	for(int i = 0; i < cnf2.size(); i++){
		cnf2[i].push_back(n2);
	}
}

void sat_sat3(int n, const vector<vector<int> > &cnf, int &n2, vector<vector<int> > &cnf2){
	n2 = n;
	cnf2.clear();
	for(int i = 0; i < cnf.size(); i++){
		int l = cnf[i].size();
		if(l <= 3){
			cnf2.push_back(cnf[i]);
			while(l++ < 3) cnf2.back().push_back(cnf[i][0]);
			continue;
		}
		cnf2.push_back((vector<int>){cnf[i][0], cnf[i][1], n2+1});
		n2++;
		for(int j = 2; j < l-2; j++, n2++){
			cnf2.push_back((vector<int>){-n2, cnf[i][j], n2+1});
		}
		cnf2.push_back((vector<int>){-n2, cnf[i][l-2], cnf[i][l-1]});
	}
}

void indset_maxcut(const graph &g, wgraph &g2){
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

void maxcut_isingModel(const wgraph &g, igraph &g2){
	int n = g.size();
	g2 = igraph(n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < g[i].size(); j++){
			g2[i].push_back((iedge){g[i][j].cst/2.0, g[i][j].dst});
		}
	}
}
