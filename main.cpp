// Ceid Upatras academic year 2013-2014
// (LEDA) implementations
// main file
#include "hw01.h"

int main()
{
    // initializations 
    int m;
    int scc,my_scc;
    int Gsize [] = { 2000, 4000, 9000 };

    // time variables 
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    
    // declare graph
    leda::graph G;

    // iterating over Gsize generating random graphs based on Gsize values
    for(unsigned int it=0; it<sizeof(Gsize)/sizeof(Gsize[0]) ; it++)
    {
        m = Gsize[it]*log(Gsize[it]);
        // create graph
        leda::random_graph(G, Gsize[it], m);

        leda::node_array<int> compnum(G,0);

        // call my_STRONG_COMPONENTS and calculate execution time
        start = std::chrono::system_clock::now();
        my_scc = my_STRONG_COMPONENTS(G, compnum);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout<<"Graph ["<<it+1<<"] "<<Gsize[it]<<"nodes, My_STRONG_COMPONENTS sccs: "<<my_scc<<std::endl;
        std::cout<<"Graph ["<<it+1<<"] "<<Gsize[it]<<"nodes, My_STRONG_COMPONENTS elapsed time: "<<elapsed_seconds.count()<<"s \n";

        // call LEDA's STRONG_COMPONENTS and calculate execution time
        start = std::chrono::system_clock::now();
        scc = my_STRONG_COMPONENTS(G, compnum);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout<<"Graph ["<<it+1<<"] "<<Gsize[it]<<"nodes, STRONG_COMPONENTS(LEDA) sccs: "<<my_scc<<std::endl;
        std::cout<<"Graph ["<<it+1<<"] "<<Gsize[it]<<"nodes, STRONG_COMPONENTS(LEDA) elapsed time: "<<elapsed_seconds.count()<<"s \n";

        if (my_STRONG_COMPONENTS_checker(G,compnum))
            std::cout<<"[my_STRONG_COMPONENTS_checker]: succeeded"<<std::endl;
        else
            std::cout<<"[my_STRONG_COMPONENTS_checker]: failed"<<std::endl;

        // initializing graph and compnum again 
        compnum.init(G,0);
        G.clear();
    }
    return 0;
}
