/* Ceid Upatras academic year 2013-2014
 * Gryllos Prokopis, Advanced Algorithms second assignment 
 * Boost, my_kruskal testing on random and grided undirected graphs.
 * main.cpp
 */
#include "hw02.h"
    
// auxiliary function to estimate execution time for my_Kruskal,boost's and ledas kruskal
// algorithm tested on given Graphs
static void test(Graph& G)
{
    Edges_Vector T; // for Boost Graphs
    leda_list<leda::edge> min_tree_edges; // for leda Graphs
    // auxiliary time variables 
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> el_s;
    // timing my_Kruskal()
    start = std::chrono::system_clock::now();
    my_Kruskal(G,T);
    end = std::chrono::system_clock::now();
    el_s = end - start;
    std::cout<<"my_Kruskal returned\nsuccessfully"<<"\n";
    std::cout<<"\t>>> elapsed time: "<<el_s.count()<<"s \n";
    std::cout<<"\t>>> Number of edges in Graph: "<<num_edges(G)<<" \n";

    // clearing Edges_Vector
    T.clear();
    // timing Boosts Kruskal_min_spanning_tree()
    start = std::chrono::system_clock::now();
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(T));
    end = std::chrono::system_clock::now();
    el_s = end - start;
    std::cout<<"boost::Kruskal_minnimum_spanning_tree\nreturned successfully"<<"\n";
    std::cout<<"\t>>> elapsed time: "<<el_s.count()<<"s \n";
    std::cout<<"\t>>> Number of edges in Graph: "<<num_edges(G)<<" \n";

    // creating a leda compatible undirected graph
    leda::graph L_G;
    L_G.make_undirected();
    leda::edge_array<int> A(L_G);
    // calling helper function to transform G into LEDA graph
    from_boost_to_leda(G,L_G,A);

    // timing Leda's min_spanning_tree()
    start = std::chrono::system_clock::now();
    min_tree_edges = MIN_SPANNING_TREE(L_G,A);
    end = std::chrono::system_clock::now();
    el_s = end - start;
    std::cout<<"leda::MIN_SPANNING_TREE\nreturned successfully"<<"\n";
    std::cout<<"\t>>> elapsed time: "<<el_s.count()<<"s \n";
    std::cout<<"\t>>> Number of edges in Graph: "<<L_G.number_of_edges()<<" \n";
}

int main()
{
    // auxiliary variables
    Distribution distribution(1, 10000);
    int Gsize_rand [] = {10000,40000,70000};
    int Gsize_grid [] = {100, 200, 300};
    Gen gen; 
    Rand_Int rng;
    

    std::cout<<"\n[Testing on RANDOM GRAPHS]\n"<<std::endl;
    for(unsigned int i=0; i<sizeof(Gsize_rand)/sizeof(Gsize_rand[0]); i++)
    {
        // create graph g based on the small world model,
        // here we constract a small-world graph with Gsize_rand[i] vertices,
        // each connected to its 6 nearest neighbors.Edges in the graph are 
        // randomly rewired to different vertices with a probability of 0.04
        Graph g(SWGen(gen, Gsize_rand[i], 8, 0.04), SWGen(), Gsize_rand[i]);
        // seeding random integer generator with system_clock 
        rng.seed(std::time(NULL));
        boost::variate_generator < Rand_Int&, Distribution > generator(rng, distribution);
        // assigning random values between 1 and 10000 to edge weights
        boost::randomize_property < boost::edge_weight_t > (g, generator);
        std::cout<<"\n\tGraph["<<i+1<<"] generated\t vertices:"<<num_vertices(g)<<std::endl;

        // call tester to calculate execution times and print
        test(g);
    }
    std::cout<<"\n[Testing on GRID GRAPHS]\n"<<std::endl;
    for(unsigned int i=0; i<sizeof(Gsize_grid)/sizeof(Gsize_grid[0]); i++)
    {
        leda::edge e;
        // create leda graph
        leda::graph g;
        // create 2 dimensional nxn grid grap
        grid_graph(g,Gsize_grid[i]);
        // edge array to store edges weights
        leda::edge_array<int> w(g,0);
        // seeding random integer generator with system_clock 
        rng.seed(std::time(NULL));
        boost::variate_generator < Rand_Int&, Distribution > generator(rng, distribution);
        // assigning random values between 1 and 10000 to edge weights
        forall_edges(e,g)
            w[e] = generator();
        Graph bg;
        from_leda_to_boost(g,w,bg);
        test(bg);
    }
    return 0;
}
