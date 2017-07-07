#ifndef _type_hpp
#define _type_hpp

#include <vector>

typedef std::vector<int> vertex;
typedef std::vector<vertex> graph;

struct edge{
	int cst, dst;
};
typedef std::vector<edge> wvertex;
typedef std::vector<wvertex> wgraph;

typedef double Num;
struct iedge{
	Num cst;
	int dst;
};
typedef std::vector<iedge> ivertex;
typedef std::vector<ivertex> igraph;

#endif
