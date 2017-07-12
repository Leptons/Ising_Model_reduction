#ifndef _reduction_hpp
#define _reduction_hpp

#include "type.hpp"

void sat_indset(int n, const std::vector<std::vector<int> > &cnf, graph &g);
void naesat3_maxcut(int n, const std::vector<std::vector<int> > &cnf, wgraph &g, bool maximize = false);
void naesat3_maxcut2(int n, const std::vector<std::vector<int> > &cnf, wgraph &g);
void sat_naesat(int n, const std::vector<std::vector<int> > &cnf, int &n2, std::vector<std::vector<int> > &cnf2);
void sat_sat3(int n, const std::vector<std::vector<int> > &cnf, int &n2, std::vector<std::vector<int> > &cnf2);
void indset_maxcut(const graph &g, wgraph &g2);
void maxcut_isingModel(const wgraph &g, igraph &g2);

#endif
