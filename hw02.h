/* Ceid Upatras academic year 2013-2014
 * Gryllos Prokopis, Advanced Algorithms second assignment 
 * Kruskal's Algorithm for finding msp on undirected 
 * graphs implementation using Boost Library
 * hw02.h
 */
#include <LEDA/graph/graph.h>
#include <LEDA/graph/min_span.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/graph/small_world_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/graph/random.hpp>
#include <time.h>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <queue>
#include <map>

// Graph type definition
typedef boost::adjacency_list < boost::vecS,boost::vecS,boost::undirectedS,
        boost::no_property,
        boost::property < boost::edge_weight_t, int > > Graph;
// weight property_map
typedef boost::property_map < Graph, boost::edge_weight_t >::type WeightMap;
typedef boost::small_world_iterator<boost::minstd_rand, Graph> SWGen;
typedef boost::uniform_int<> Distribution; 
// i am going to use that to create random ints for the edges weights
// and this to form the propabillity during graph creation, don't realy know the difference.
typedef boost::minstd_rand Gen;
typedef boost::mt19937 Rand_Int; 
typedef std::vector < boost::graph_traits < Graph >::edge_descriptor > Edges_Vector;

// auxiliary typedefs for later use
typedef boost::graph_traits<Graph>::edge_iterator edge_it;
typedef boost::graph_traits<Graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<Graph>::vertex_iterator vertex_it;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_desc;

// my_Kruskal prototype
void my_Kruskal(Graph& g, Edges_Vector& T);

// helper function that creates leda suitable graph from a given boost graph
void from_boost_to_leda(Graph& g_in, leda::graph& g_out, leda::edge_array<int>& W);
