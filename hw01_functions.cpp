#include "hw01.h"

using namespace leda;

// STRONG_C0MPONENTS implementation to find scc's of a given graph
int my_STRONG_COMPONENTS(graph& G, node_array<int>& compnum2)
{
    // declarations
    int count = 0;
    int n = G.number_of_nodes();

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
    G.rev_all_edges();

    for(int i=n; i>0; i--)
    { 
        if (!reached[LN1[i]]) 
        {
            LN2 = DFS(G,LN1[i],reached);
            forall(y,LN2)
                compnum2[y] = count;
            count++;
        }
    }
    return count;
}

// checker to validate my_STRONG_COMPONENTS results
bool my_STRONG_COMPONENTS_checker(graph& G, node_array<int>& compnum)
{
    // declarations
    bool test = true;
    int count;
    // for temp,I use an initial value that is highly unlikely 
    // for compnum to occur so that there is no conflict during 
    // the comparisons
    int temp=1000;

    node x,y;
    list<node> LN;
    node_array<bool> reached(G,false);

    // testing my_STRONG_COMPONENTS 
    count = my_STRONG_COMPONENTS(G,compnum);

    forall_nodes(x,G)
    {
        if (temp!=compnum[x])
        {
            temp = compnum[x];
            LN = DFS(G,x,reached);

            forall_nodes(y,G)
            {
                if (compnum[y]==temp && reached[y]==false)
                {
                    test=false;
                    return test;
                }
            }

            G.rev_all_edges();
            reached.init(G,false);
            LN = DFS(G,x,reached);
            forall_nodes(y,G)
            {
                if (compnum[y]==temp && reached[y]==false)
                {
                    test=false;
                    return test;
                }
            }
        }
    }

    return test;
}
