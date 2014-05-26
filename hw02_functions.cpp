/* Ceid Upatras academic year 2013-2014
 * Gryllos Prokopis, Advanced Algorithms second assignment 
 * Kruskal's algorithm implementation, using boost lib
 * hw02_functions.cpp 
 */

#include "hw02.h"

using namespace boost;

void my_Kruskal(Graph& g, WeightMap& wm, Edges_Vector& T)
{
    // auxiliary typedefs for later use
    typedef graph_traits<Graph>::edge_iterator edge_it;
    typedef graph_traits<Graph>::edge_descriptor edge_desc;
    typedef graph_traits<Graph>::vertex_iterator vertex_it;
    typedef graph_traits<Graph>::vertex_descriptor vertex_desc;
    typedef property_traits<WeightMap>::value_type W_value;
    typedef indirect_cmp<WeightMap, std::greater<W_value> > weight_greater;

    // instead of creating a separate list for earch vertex we will use a map
    // that maps vertices to their list of vertices, first try using boost's ptr_map
    ptr_map<vertex_desc, std::vector<vertex_desc> > vert_map;

    // creating pair of iterators for vertices and edges
    std::pair<edge_it, edge_it> ei;
    std::pair<vertex_it, vertex_it> vi;
    weight_greater wl(wm);
    // creating a priority queue in increasing order of edges weights
    std::priority_queue<edge_desc, std::vector<edge_desc>, weight_greater> sorted_edges(wl); 
    // iterate over edges and push all edges into sorted_edges vector
    for (ei=edges(g); ei.first != ei.second; ++ei.first) 
    {
        sorted_edges.push(*ei.first);   
    }

    // iterating over vertices and creating lists for each vertex
    // then assign those lists to the vertices through the vert_map
    for (vi=vertices(g); vi.first != vi.second; ++vi.first) 
    {
        std::vector<vertex_desc> L;
        L.push_back(*vi.first);
        vert_map[*vi.first] = L;
    }

    // main loop to create mst
    edge_desc aux_e;
    vertex_desc v,u;
    for(;;)
    {   
        // choose edge with lowest weight
        aux_e = sorted_edges.top();
        // get vertices that append to edge
        u = source(aux_e, g);
        v = target(aux_e, g);
        if (vert_map[u].front() != vert_map[v].front())
        {
            // if statement true then aux_e belongs to mst
            T.push_back(aux_e);
            // creating auxiliary vector
            std::vector<vertex_desc> L1L2;
            // preallocate memory for merged vector
            L1L2.reserve(vert_map[u].size() + vert_map[v].size() );  
            // merge vectors 
            if (vert_map[u].size()>=vert_map[v].size())
            {
                // create merged vector
                L1L2.insert( L1L2.end(), vert_map[u].begin(), vert_map[u].end() );
                L1L2.insert( L1L2.end(), vert_map[v].begin(), vert_map[v].end() );
            }
            else
            {
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

