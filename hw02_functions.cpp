/* Ceid Upatras academic year 2013-2014
 * Gryllos Prokopis, Advanced Algorithms second assignment 
 * Kruskal's algorithm implementation, using boost lib
 * hw02_functions.cpp 
 */

#include "hw02.h"

using namespace boost;

void my_Kruskal(Graph& g, Edges_Vector& T)
{
    // auxiliary typedefs for later use
    typedef property_traits<WeightMap>::value_type W_value;
    typedef indirect_cmp<WeightMap, std::greater<W_value> > weight_greater;

    // instead of creating a separate list for earch vertex we will use a map
    // that maps vertices to their list of vertices, first try using boost's ptr_map
    ptr_map<vertex_desc, std::vector<vertex_desc> > vert_map;

    // creating pair of iterators for vertices and edges
    std::pair<edge_it, edge_it> ei;
    std::pair<vertex_it, vertex_it> vi;
    
    WeightMap wm = get(edge_weight, g);
    weight_greater wl(wm);
    // creating a priority queue in increasing order of edges weights
    std::priority_queue<edge_desc, std::vector<edge_desc>, weight_greater> sorted_edges(wl); 
    // iterate over edges and push all edges into sorted_edges vector
    for (ei=edges(g); ei.first != ei.second; ++ei.first) 
        sorted_edges.push(*ei.first);   

    // iterating over vertices and creating lists for each vertex
    // then assign those lists to the vertices through the vert_map
    for (vi=vertices(g); vi.first != vi.second; ++vi.first){
        std::vector<vertex_desc> L;
        L.push_back(*vi.first);
        vert_map[*vi.first] = L;
    }

    // main loop to create mst
    edge_desc aux_e;
    vertex_desc v,u;
    for(;;){   
        // choose edge with lowest weight
        aux_e = sorted_edges.top();
        // get vertices that append to edge
        u = source(aux_e, g);
        v = target(aux_e, g);
        if (vert_map[u].front() != vert_map[v].front()){
            // if statement true then aux_e belongs to mst
            T.push_back(aux_e);
            // creating auxiliary vector
            std::vector<vertex_desc> L1L2;
            // preallocate memory for merged vector
            L1L2.reserve(vert_map[u].size() + vert_map[v].size() );  
            // merge vectors 
            if (vert_map[u].size()>=vert_map[v].size()){
                // create merged vector
                L1L2.insert( L1L2.end(), vert_map[u].begin(), vert_map[u].end() );
                L1L2.insert( L1L2.end(), vert_map[v].begin(), vert_map[v].end() );
            }
            else{
                // create merged vector
                L1L2.insert( L1L2.end(), vert_map[v].begin(), vert_map[v].end() );
                L1L2.insert( L1L2.end(), vert_map[u].begin(), vert_map[u].end() );
            }
            // point both vertices to the merged vector through vert_map
            vert_map[u] = L1L2;
            vert_map[v] = L1L2;
        }   
        // removing used edge from sorted_edges
        sorted_edges.pop();
        if (T.size() == num_vertices(g)-1)
            break;
    }
    return;
}

// implementation of helper function that transforms Boost Graph to Leda Graph.
// the given Graph g_in must be undirected otherwise this function will fail.
void from_boost_to_leda(Graph& g_in, leda::graph& g_out)
{
    unsigned int n =  num_vertices(g_in);
    unsigned int e =  num_edges(g_in);

    // create a map, to map g_in vertices to g_out nodes
    std::map<vertex_desc,leda::node> btl_map;
    // iterate over all g_in vertices, creating nodes for its vertex, and mapping 
    // them together
    std::pair<vertex_it, vertex_it> vp;
    for (vp = vertices(g_in); vp.first != vp.second; ++vp.first){
        leda::node v =  g_out.new_node(); 
        btl_map[*vp.first] = v;
    }
    // iterate over all g_in edges and create corresponding edge to g_out
    std::pair<edge_it, edge_it> ei;
    for (ei = edges(g_in); ei.first != ei.second; ++ei.first){
        leda::node s = btl_map[source(*ei.first,g_in)];
        leda::node t = btl_map[target(*ei.first,g_in)];
        leda::edge e = g_out.new_edge(s,t);
    }
    return;
}
