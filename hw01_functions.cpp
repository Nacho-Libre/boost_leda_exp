// Ceid Upatras academic year 2013-2014
// (LEDA) implementations
// functions file

#include "hw01.h"

using namespace leda;

// my_STRONG_C0MPONENTS tries to find all scc's of a given graph
// it returns an integer which represents how many scc's it found
// and updates LEDA's built-in data type node_array compnum
// assigning each node with scc's id it belongs to.
int my_STRONG_COMPONENTS(graph& G, node_array<int>& compnum)
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

    // starting from the node with the highest completition time
    // we run LEDA's dfs algorithm on G_rev and calculate how 
    // many nodes where reached, those nodes should make up a 
    // scc, we update compnum with the id of the scc they belong
    // to (eg  scc: 0, scc: 1, scc: 2) 
    for(int i=n; i>0; i--)
    { 
        if (!reached[LN1[i]]) 
        {
            LN2 = DFS(G,LN1[i],reached);
            forall(y,LN2)
                compnum[y] = count;
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

    // for some the nodes of G that belong to the same
    // scc (at least for one for every scc). based on what
    // my_STRONG_COMPONENTS returned, we run leda's dfs 
    // algorithm and then check if every node in the scc
    // was reached, if all nodes were reached we then reverse
    // all the edges of G and do exactly the same, if again 
    // all nodes have been reached the function returns true
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
