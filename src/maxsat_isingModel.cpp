// MAX SAT -> MAX NAE SAT -> MAX NAE 3SAT -> MAXCUT -> Ising Model
#include "type.hpp"
#include "io.hpp"
#include "reduction.hpp"
#include <iostream>

using namespace std;

int main(){
	int n, n2, n3;
	vector<vector<int> > cnf, cnf2, cnf3;
	wgraph g;
	igraph g2;

	inputSat(n, cnf);

	sat_naesat(n, cnf, n2, cnf2);
	sat_sat3(n2, cnf2, n3, cnf3);
	naesat3_maxcut(n3, cnf3, g, true);
	maxcut_isingModel(g, g2);

	outputIsingModel(g2);
	return 0;
}
