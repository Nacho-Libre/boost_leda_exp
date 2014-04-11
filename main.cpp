// Ceid Upatras academic year 2013-2014
// experimental use of LEDA's built-in functions and data types
// file main.cpp
#include "hw01.h"

int main()
{

    // auxiliary variables and arrays
    int m;
    int scc,my_scc;
    int Gsize1 [] = { 2000, 4000, 9000 };
    int Gsize2 [] = { 1000, 4000, 9000 };
    int cliques [] = { 5, 10, 20 };

    // time variables 
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    
    // declare graph G and an auxiliary graph temp
    leda::graph G,temp;

    // iterating over Gsize1 and generating random graphs with leda's
    // random_graph(). For each Graph created my_STRONG_COMPONENTS()
    // and leda's STRONG_COMPONENTS() are called and timed. At the end
    // of every iteration my_STRONG_COMPONENTS_checker is called to 
    // evaluate my_STRONG_COMPONENTS() results.
    for(unsigned int it=0; it<sizeof(Gsize1)/sizeof(Gsize1[0]); it++)
    {
        m = Gsize1[it]*log(Gsize1[it]);
        // create graph
        leda::random_graph(G, Gsize1[it], m);
  
        leda::node_array<int> compnum(G,0);
  
        // call my_STRONG_COMPONENTS and calculate execution time
        start = std::chrono::system_clock::now();
        my_scc = my_STRONG_COMPONENTS(G, compnum);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout<<"Graph ["<<it+1<<"] "<<Gsize1[it]<<"nodes, My_STRONG_COMPONENTS sccs: "<<my_scc<<std::endl;
        std::cout<<"Graph ["<<it+1<<"] "<<Gsize1[it]<<"nodes, My_STRONG_COMPONENTS elapsed time: "<<elapsed_seconds.count()<<"s \n";
  
        // call LEDA's STRONG_COMPONENTS and calculate execution time using
        start = std::chrono::system_clock::now();
        scc = STRONG_COMPONENTS(G, compnum);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout<<"Graph ["<<it+1<<"] "<<Gsize1[it]<<"nodes, STRONG_COMPONENTS(LEDA) sccs: "<<my_scc<<std::endl;
        std::cout<<"Graph ["<<it+1<<"] "<<Gsize1[it]<<"nodes, STRONG_COMPONENTS(LEDA) elapsed time: "<<elapsed_seconds.count()<<"s \n";
  
        if (my_STRONG_COMPONENTS_checker(G,compnum))
            std::cout<<"[my_STRONG_COMPONENTS_checker]: succeeded"<<std::endl;
        else
            std::cout<<"[my_STRONG_COMPONENTS_checker]: failed"<<std::endl;
  
        // initializing graph and compnum again 
        compnum.init(G,0);
        G.clear();
    }

    // iterating over Gsize2 
    for (unsigned int it=0; it<sizeof(Gsize2)/sizeof(Gsize2[0]); it++)
    {
        // in this loop the cliqued graphs are created
        for (unsigned int it1=0; it1<cliques[it]; it1++) 
        {
            // creating a clique 
            leda::complete_graph(temp, Gsize2[it]/cliques[it]);        
            // merging clique with the rest of the graph, it still remains unclear 
            // on which node of the existing graph does the clique connect to
            G.join(temp);
        }

        G.clear();
    }
    return 0;
}
