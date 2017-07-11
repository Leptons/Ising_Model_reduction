// SAT -> INDSET -> MAXCUT -> Ising Model
#include "type.hpp"
#include "io.hpp"
#include "reduction.hpp"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	graph g;
	wgraph g2;
	igraph g3;

	bool isDirected = false, isVertexBased = false, isZeroIndexed = false;
	for(int i = 1; i < argc; i++){
		string option(argv[i]);
		if(option == "-undirected" || option == "-u") isDirected = false;
		else if(option == "-directed" || option == "-d") isDirected = true;
		else if(option == "-vertex" || option == "-v") isVertexBased = true;
		else if(option == "-edge" || option == "-e") isVertexBased = false;
		else if(option == "-zero" || option == "-z") isZeroIndexed = true;
		else if(option == "-one" || option == "-o") isZeroIndexed = false;
		else cerr << "Unknown command line flag: " + option << endl;
	}

	inputIndset(g, isDirected, isVertexBased, isZeroIndexed); 

	indset_maxcut(g, g2);
	maxcut_isingModel(g2, g3);

	outputIsingModel(g3);

	return 0;
}
