// Ceid Upatras academic year 2013-2014
// (LEDA) implementations
// header file

#include <LEDA/graph/graph.h>
#include <LEDA/graph/node_array.h>
#include <LEDA/graph/basic_graph_alg.h>
#include <math.h>
#include <iostream>

using namespace leda;

// my_STRONG_C0MPONENTS declaration
int my_STRONG_COMPONENTS(leda::graph& G, leda::node_array<int>& compnum2);

// my_STRONG_C0MPONENTS checker declaration
bool my_STRONG_COMPONENTS_checker(leda::graph& G, leda::node_array<int>& compnum);
