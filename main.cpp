#include "hw01.h"

int main()
{
    // initializations 
    int n,m;
    int size [] = { 20,40,90 };
    
    // declare graph
    graph G;

    // generating random graphs
    for(unsigned int it=0; it<sizeof(size)/sizeof(size[0]) ; it++)
    {
        m = size[it]*log(size[it]);
        // create graph
        random_graph(G, size[it], m);
        
    }
    return 0;
}
