// SAT -> INDSET -> MAXCUT -> Ising Model
#include "type.hpp"
#include "io.hpp"
#include "reduction.hpp"

using namespace std;

int main(){
	int n;
	vector<vector<int> > cnf;

	inputSat(n, cnf);

	graph g;
	wgraph g2;
	igraph g3;

	sat_indset(n, cnf, g);
	indset_maxcut(g, g2);
	maxcut_isingModel(g2, g3);

	outputIsingModel(g3);

	return 0;
}
