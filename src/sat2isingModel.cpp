// SAT -> INDSET -> MAXCUT -> Ising Model
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

typedef vector<int> vertex;
typedef vector<vertex> graph;

struct edge{
	int cst, dst;
};
typedef vector<edge> wvertex;
typedef vector<wvertex> wgraph;

typedef double Num;
struct iedge{
	Num cst;
	int dst;
};
typedef vector<iedge> ivertex;
typedef vector<ivertex> igraph;

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

int main(){
	int n;
	vector<vector<int> > cnf;

	inputSat(n, cnf);

	graph g;
	wgraph g2;
	igraph g3;

	sat2indset(n, cnf, g);
	indset2maxcut(g, g2);
	maxcut2isingModel(g2, g3);

	outputIsingModel(g3);

	return 0;
}
