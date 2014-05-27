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
void from_boost_to_leda(Graph& b_g, leda::graph& l_g, leda::edge_array<int>& W) 
{
    WeightMap wm = get(edge_weight, b_g);

    // create a map, to map g_in vertices to g_out nodes
    // and a map to map edges of b_g to edges of l_g
    std::map<vertex_desc, leda::node> vtn_map;
    std::map<edge_desc, leda::edge> ete_map;
    // iterate over all g_in vertices, creating nodes for its vertex, and mapping 
    // them together
    std::pair<vertex_it, vertex_it> vp;
    for (vp = vertices(b_g); vp.first != vp.second; ++vp.first){
        leda::node v =  l_g.new_node(); 
        vtn_map[*vp.first] = v;
    }
    // iterate over all g_in edges and create corresponding edge to g_out
    // and assigning weights.
    std::pair<edge_it, edge_it> ei;
    for (ei = edges(b_g); ei.first != ei.second; ++ei.first){
        leda::node s = vtn_map[source(*ei.first,b_g)];
        leda::node t = vtn_map[target(*ei.first,b_g)];
        leda::edge e = l_g.new_edge(s,t);
        ete_map[*ei.first] = e;
    }
    // edge array to store edges weights
    leda::edge_array<int> w(l_g,0);
    for (ei = edges(b_g); ei.first != ei.second; ++ei.first)
        w[ete_map[*ei.first]] = wm[*ei.first];
    W = w; 
    return;
}

// implementation of helper function that makes a Leda Graph boost compatible.
void from_leda_to_boost(leda::graph& l_g, leda::edge_array<int>& W, Graph& b_g) 
{
    // create a map,to map leda's nodes with boost's vertices.
    // and a map to map edges of l_g to b_g
    std::map<leda::node, vertex_desc> ntv_map;
    // auxiliary variables
    leda::edge e;
    leda::node n;

    forall_nodes(n,l_g){
        vertex_desc v = add_vertex(b_g);
        ntv_map[n] = v;
    }
    WeightMap wm = get(edge_weight, b_g);
    forall_edges(e,l_g){
        edge_desc u = add_edge(ntv_map[l_g.source(e)],ntv_map[l_g.target(e)],b_g).first;
        wm[u] = W[e];
    }
    return;
}
