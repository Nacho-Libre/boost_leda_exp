/* Ceid Upatras academic year 2013-2014
 * Gryllos Prokopis, Advanced Algorithms second assignment 
 * Kruskal's Algorithm for finding msp on undirected 
 * graphs implementation using Boost Library
 * hw02.h
 */
#include <boost/graph/adjacency_list.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/graph/small_world_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/graph/random.hpp>
#include <time.h>
#include <iostream>
#include <queue>
#include <chrono>

typedef boost::adjacency_list < boost::vecS,boost::vecS,boost::undirectedS,
        boost::no_property,
        boost::property < boost::edge_weight_t, int > > Graph;
typedef boost::property_map < Graph, boost::edge_weight_t >::type WeightMap;
typedef boost::small_world_iterator<boost::minstd_rand, Graph> SWGen;
typedef boost::uniform_int<> Distribution; 
// i am going to use that to create random ints for the edges weights
// and this to form the propabillity during graph creation, don't realy know the difference.
typedef boost::minstd_rand Gen;
typedef boost::mt19937 Rand_Int; 
typedef std::vector < boost::graph_traits < Graph >::edge_descriptor > Edges_Vector;

// my_Kruskal prototype
void my_Kruskal(Graph& g, WeightMap& wm, Edges_Vector& T);
