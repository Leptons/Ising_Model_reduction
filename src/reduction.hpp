#ifndef _reduction_hpp
#define _reduction_hpp

#include "type.hpp"

void sat2indset(int n, const std::vector<std::vector<int> > &cnf, graph &g);
void indset2maxcut(const graph &g, wgraph &g2);
void maxcut2isingModel(const wgraph &g, igraph &g2);

#endif
