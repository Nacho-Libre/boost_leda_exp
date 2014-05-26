/* Ceid Upatras academic year 2013-2014
 * Gryllos Prokopis, Advanced Algorithms second assignment 
 * Boost, my_kruskal testing on random and grided undirected graphs.
 * main.cpp
 */
#include "hw02.h"
    
// auxiliary function to estimate execution time for my_Kruskal,boost's and ledas kruskal
// algorithm tested on given Graphs
static void test(Graph& G, Edges_Vector& T)
{
    // auxiliary time variables 
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> el_s;

    // timing my_Kruskal()
    start = std::chrono::system_clock::now();
    my_Kruskal(G, T);
    end = std::chrono::system_clock::now();
    el_s = end - start;
    std::cout<<"my_Kruskal returned\nsuccessfully"<<"\n";
    std::cout<<"\t>>> elapsed time: "<<el_s.count()<<"s \n";
    std::cout<<"\t>>> Number of edges in Graph: "<<num_edges(G)<<"s \n";
    std::cout<<"\t>>> Number of edges in msp: "<<T.size()<<"s \n";

    // clearing Edges_Vector
    T.clear();
    // timing Boosts Kruskal_min_spanning_tree()
    start = std::chrono::system_clock::now();
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(T));
    end = std::chrono::system_clock::now();
    el_s = end - start;
    std::cout<<"boost::Kruska_minnimum_spanning_tree\nreturned successfully"<<"\n";
    std::cout<<"\t>>> elapsed time: "<<el_s.count()<<"s \n";
    std::cout<<"\t>>> Number of edges in Graph: "<<num_edges(G)<<"s \n";
    std::cout<<"\t>>> Number of edges in msp: "<<T.size()<<"s \n";
}

int main()
{

    // auxiliary variables
    Edges_Vector T;
    Distribution distribution(1, 10000);
    int Gsize_rand [] = {10000, 40000, 70000};
    // int Gsize_grid [] = { 4000, 8000, 15000 };
    Gen gen; 
    Rand_Int rng;
    

    std::cout<<"\n[Testing on random graphes]\n"<<std::endl;
    for(unsigned int i=0; i<sizeof(Gsize_rand)/sizeof(Gsize_rand[0]); i++)
    {
        // create graph g based on the small world model,
        // here we constract a small-world graph with Gsize_rand[i] vertices,
        // each connected to its 6 nearest neighbors.Edges in the graph are 
        // randomly rewired to different vertices with a probability of 0.04
        Graph g(SWGen(gen, Gsize_rand[i], 6, 0.04), SWGen(), Gsize_rand[i]);
        // #TODO create some tests to ensure that the generated graph
        // has no unconnected vertices using dfs_search etc

        // create property map so that we can access properties
        // WeightMap wm = boost::get(boost::edge_weight, g);

        // seeding random integer generator with system_clock 
        rng.seed(std::time(NULL));
        boost::variate_generator < Rand_Int&, Distribution > generator(rng, distribution);
        // assigning random values between 1 and 10000 to edge weights
        boost::randomize_property < boost::edge_weight_t > (g, generator);
        std::cout<<"\n\tGraph["<<i+1<<"] generated\t vertices:"<<num_vertices(g)<<std::endl;

        // call tester to calculate execution times and print
        test(g,T);

        // initializing graph again 
        g.clear();
    }
    return 0;
}
