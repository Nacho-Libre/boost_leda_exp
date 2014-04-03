#include <LEDA/graph/graph.h>
#include <LEDA/graph/node_array.h>
#include <LEDA/graph/basic_graph_alg.h>
#include <math.h>
#include <vector>
#include <iostream>

using namespace leda;

int my_STRONG_COMPONENTS(const graph& G, node_array<int>& compnum2)
{
    // declarations
    int count = 0;
    int n = G.number_of_nodes();

    graph G_rev;
    node x,y;
    node_array<int> dfsnum(G,0);
    node_array<int> compnum1(G,0);
    node* LN1 = new node[n] ;
    list<node> LN2;
    node_array<bool> reached(G,false);


    // dfs on G to get completion times 
    DFS_NUM(G,dfsnum,compnum1);
    // using completion times to create a sorted node array
    forall_nodes(x,G)
    {
       LN1[compnum1[x]] = x;
    }
    // creating G_rev
    G_rev = G;
    G_rev.rev_all_edges();

   // for(int i=n; i>0; i--)
   // { 
   //     if ( !reached[LN1[i]] ) 
   //     {
   //         LN2 = DFS(G_rev,LN1[i],reached);
   //         forall(y,LN2) compnum2[y] = count;
   //         count++;
   //     }
   // }
   // return count;
}


