#ifndef _io_hpp
#define _io_hpp

#include "type.hpp"

void inputSat(int &n, std::vector<std::vector<int> > &cnf); // assume SAT competition format
void inputIndset(graph &g, bool isDirected, bool isVertexBased, bool isZeroIndexed);
void outputIndset(const graph &g);
void outputIsingModel(const igraph &g, int opt = -1);

#endif
