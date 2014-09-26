// Ceid Upatras academic year 2013-2014
// experimental use of LEDA's built-in functions and data types
// file main.cpp
#include "hw01.h"
    
// auxiliary function to estimate execution time for both my_STRONG_COMPONENTS & STRONG_COMPONENTS
static void test(leda::graph& G, leda::node_array<int>& compnum,
        std::chrono::duration<double>& el_s1, std::chrono::duration<double>& el_s2)
{
    int scc,my_scc;
    // auxiliary time variables 
    std::chrono::time_point<std::chrono::system_clock> start, end;

    // timing my_STRONG_COMPONENTS()
    start = std::chrono::system_clock::now();
    my_scc = my_STRONG_COMPONENTS(G, compnum);
    end = std::chrono::system_clock::now();
    el_s1 = end - start;
    std::cout<<"My_STRONG_COMPONENTS SCCs: "<<my_scc<<"\n";

    // timing LEDA'S STRONG_COMPONENTS()
    start = std::chrono::system_clock::now();
    scc = STRONG_COMPONENTS(G, compnum);
    end = std::chrono::system_clock::now();
    el_s2 = end - start;
    std::cout<<"STRONG_COMPONENTS(LEDA) SCCs: "<<scc<<"\n";

    // validate my_STRONG_COMPONENTS results using the checker 
    if (my_STRONG_COMPONENTS_checker(G,compnum))
        std::cout<<"[my_STRONG_COMPONENTS_checker]: succeeded"<<std::endl;
    else
        std::cout<<"[my_STRONG_COMPONENTS_checker]: failed"<<std::endl;
}

int main()
{

    // auxiliary variables
    int m;
    int Gsize1 [] = { 20000, 40000, 90000 };
    int Gsize2 [] = { 4000, 8000, 15000 };
    unsigned int cliques [] = { 5, 10, 20 };
    leda::node temp_n1,temp_n2,x;
    leda::list<leda::node> LN;
    std::chrono::duration<double> elapsed_seconds1,elapsed_seconds2;
    
    // declare graph G and auxiliary graph temp
    leda::graph G,temp;
    leda::node_array<bool> reached(G,false);

    // creating random graphs with leda's random_graph().
    // For each Graph created my_STRONG_COMPONENTS()
    // and leda's STRONG_COMPONENTS() are called and timed using a helper
    // function "test". At the end of every iteration my_STRONG_COMPONENTS_checker
    // is called to evaluate my_STRONG_COMPONENTS() results.
    std::cout<<"\n[Testing on random graphes]\n"<<std::endl;
    for(unsigned int it=0; it<sizeof(Gsize1)/sizeof(Gsize1[0]); it++)
    {
        m = Gsize1[it]*log(Gsize1[it]);
        // create graph
        leda::random_graph(G, Gsize1[it], m);
  
        leda::node_array<int> compnum(G,0);
  
        std::cout<<"Graph["<<it+1<<"] generated\t nodes:"<<G.number_of_nodes()<<std::endl;
        // call tester to calculate execution times
        test(G,compnum,elapsed_seconds1,elapsed_seconds2);
        std::cout<<"\t>>> My_STRONG_COMPONENTS elapsed time: "<<elapsed_seconds1.count()<<"s \n";
        std::cout<<"\t>>> STRONG_COMPONENTS(LEDA) elapsed time: "<<elapsed_seconds2.count()<<"s \n";
  
  
        // initializing graph and compnum again 
        compnum.init(G,0);
        G.clear();
    }

    std::cout<<"\n[Testing on cliqued graphes]\n"<<std::endl;
    // creating cliqued graphs
    for (unsigned int it=0; it<sizeof(Gsize2)/sizeof(Gsize2[0]); it++)
    {
        // creating the first clique 
        leda::complete_graph(temp, Gsize2[it]/cliques[it]);        
        // adding clique to the graph
        G.join(temp);

        // we now chose random nodes from the first clique
        // temp_n1 is going to be used as starting node for dfs.
        // this will ensure us that an unreached node belongs
        // to the newest clique.
        // temp_n2 is going to be used a pointer to a node from
        // the last added clique, so that we can do the linking with
        // the next clique
        temp_n1 = G.choose_node();
        temp_n2 = G.choose_node();

        // in this loop, the rest of the cliques are going to be created 
        // and added to the rest of the graph
        for (unsigned int it1=1; it1<cliques[it]; it1++) 
        {
            leda::complete_graph(temp, Gsize2[it]/cliques[it]);        
            G.join(temp);
            // we are going to run DFS on graph G, the nodes that 
            // are not reached are part of the most recently created clique
            reached.init(G,false);
            LN = DFS(G,temp_n1,reached);
            forall_nodes(x,G)
            {
                // for the first unreached node we find (which should be part
                // of the newest clique) we create an edge to connect it with a
                // random node from the previews clique and then we store that 
                // node to use it for the next linking
                if (!reached[x])
                {
                    G.new_edge(temp_n2,x);
                    temp_n2 = x;
                    break;
                }
            }
        }

        // using test function to get elapsed times
        leda::node_array<int> compnum(G,0);
        std::cout<<"Graph["<<it+1<<"] generated\t nodes:"<<G.number_of_nodes()<<std::endl;
        test(G,compnum,elapsed_seconds1,elapsed_seconds2);
        std::cout<<"\t>>> My_STRONG_COMPONENTS elapsed time: "<<elapsed_seconds1.count()<<"s \n";
        std::cout<<"\t>>> STRONG_COMPONENTS(LEDA) elapsed time: "<<elapsed_seconds2.count()<<"s \n";

        compnum.init(G,0);
        G.clear();
    }
    return 0;
}
