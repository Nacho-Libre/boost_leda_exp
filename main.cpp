#include "hw01.h"

int main()
{
    // initializations 
    int m;
    int scc,scc_test;
    int Gsize [] = { 20};
    bool test;
    
    // declare graph
    leda::graph G;


    // generating random graphs
    for(unsigned int it=0; it<sizeof(Gsize)/sizeof(Gsize[0]) ; it++)
    {
        m = Gsize[it]*log(Gsize[it]);
        // create graph
        leda::random_graph(G, Gsize[it], m);

        leda::node_array<int> compnum(G,0);
        // call my_STRONG_COMPONENTS 
        scc_test = my_STRONG_COMPONENTS(G, compnum);
        test = my_STRONG_COMPONENTS_checker(G,compnum);
        // initializing compnum again 
        compnum.init(G,0);
        // using leda's STRONG_COMPONENTS to test our results
         // scc = STRONG_COMPONENTS(G, compnum);
         // std::cout<<"["<<it+1<<"] My_STRONG_COMPONENTS results: "<<scc_test<<std::endl;
         // std::cout<<"["<<it+1<<"] STRONG_COMPONENTS results: "<<scc<<std::endl;
        G.clear();

        
    }
    return 0;
}
