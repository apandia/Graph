#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Find Minimum Spanning Tree - Kruskal Algorithm

/* Approach:
 * 1. Sort all the edges according to their weight
 * 2. Greedily pick minimum edge and make sure the two nodes belong to different components
 *    (using disjoint set data structure findParent operation).
 * 3. Once we a node to be a part of the MST, we must join the two components using the union operation of DSU.
 */

/*
Input Graph:

           2    3
        0----1----2
        |   /|   /
      6 | 8/ |5 / 7
        | /  | /
        3    4

Output:
Minimum Spanning Tree:
0->1
1->2
0->3
1->4

Cost of MST =  = 16

           2    3
        0----1----2
        |    |
      6 |    |5
        |    |
        3    4

Total weight = 6+2+5+3 = 16
*/

//TC: O(E logE) + O(E*4*alpha)      [E logE for sorting and E*4*alpha for findParent operation ‘E’ times]
//SC: O(N)+ O(N)                    [Parent array + Rank Array]

struct node{
    int u;
    int v;
    int w;

    node(int first, int second, int weight)
    {
        u = first;
        v = second;
        w = weight;
    }
};

bool comparison(node a, node b)
{
    return a.w < b.w;
}

int findParent(int u, vector<int>& parent)
{
    if(u == parent[u])
        return u;

    parent[u] = findParent(parent[u], parent);

    return parent[u];
}

void unionNodes(int u, int v, vector<int>& parent, vector<int>& rank)
{
    u = findParent(u, parent);
    v = findParent(v, parent);

    if(rank[u] < rank[v])
    {
        parent[u] = v;
    }
    else if(rank[u] > rank[v])
    {
        parent[v] = u;
    }
    else
    {
        parent[v] = u;
        rank[u]++;
    }
}

int main()
{
    int numNode = 5;

    vector<node> edge;

    edge.push_back(node(0,1,2));
    edge.push_back(node(1,0,2));
    edge.push_back(node(0,3,6));
    edge.push_back(node(3,0,6));
    edge.push_back(node(1,2,3));
    edge.push_back(node(2,1,3));
    edge.push_back(node(1,3,8));
    edge.push_back(node(3,1,8));
    edge.push_back(node(1,4,5));
    edge.push_back(node(4,1,5));
    edge.push_back(node(2,4,7));
    edge.push_back(node(4,2,7));

    sort(edge.begin(), edge.end(), comparison);

    vector<int> parent(numNode);
    for(int i = 0; i < numNode; i++)
        parent[i] = i;

    vector<int> rank(numNode, 0);

    int cost = 0;
    vector<pair<int, int>> mst;

    for(auto it : edge)
    {
        if(findParent(it.v, parent) != findParent(it.u, parent))
        {
            mst.push_back({it.u, it.v});
            cost += it.w;
            unionNodes(it.u, it.v, parent, rank);
        }
    }

    cout<<"Minimum Spanning Tree: "<<endl;
    for(auto it : mst)
        cout<<it.first<<" -> "<<it.second<<endl;

    cout<<endl;
    cout<<"Cost of MST = "<<cost<<endl;

    return 0;
}
