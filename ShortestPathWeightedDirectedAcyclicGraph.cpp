#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Shortest path from source node in directed acyclic weighted graph - topological sort
/*
Input Directed Graph:

           2      3      6
        0----->1----->2----->3
        |             ^      ^
      1 |             |      | 1
        |             |      |
        L------------>4----->5
                         4

Adjacency List graph:
Vertex[0]-> [1, 2][4, 1]
Vertex[1]-> [2, 3]
Vertex[2]-> [3, 6]
Vertex[3]->
Vertex[4]-> [2, 2][5, 4]
Vertex[5]-> [3, 1]

Output:
Shortest path from source 0:
0 -> 0 : 0
0 -> 1 : 2
0 -> 2 : 3
0 -> 3 : 6
0 -> 4 : 1
0 -> 5 : 5
*/

class Graph{
public:
    Graph(int V)
    {
        numVertex = V;
        adjList = new vector<pair<int,int>>[numVertex];
    }

    void addEdge(int u, int v, int w)
    {
        adjList[u].push_back({v, w});
    }

    void printAdjecencyList()
    {
        for(int i =0; i< numVertex; i++)
        {
            cout<<"Vertex["<<i<<"]-> ";
            for(auto it : adjList[i])
            {
                cout<<"["<<it.first<<", "<<it.second<<"]";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    vector<int> shortestPathFromSource(int src);

    void toposort(int src, vector<int>& visited, stack<int>& topo)
    {
        visited[src] = 1;
        for(auto neighbour : adjList[src])
        {
            if(visited[neighbour.first] == 0)
            {
                toposort(neighbour.first, visited, topo);
            }
        }
        topo.push(src);
    }

private:
    int numVertex;
    vector<pair<int, int>>* adjList;
};

//TC : O(N+E) + O(N+E) = O(N+E)x2  [one for finding toposort and another for finding distance]
//SC : O(N)   + O(N)   = O(2N)     [for stack and visited array, not considering adj list space]
//Aux: O(N)                        [recursive stack space used in DFS. O(1) if BFS is used]
vector<int> Graph::shortestPathFromSource(int src)
{
    vector<int> visited(numVertex, 0);
    stack<int> topo;

    if(visited[src] == 0)
    {
        toposort(src, visited, topo);
    }

    vector<int> distance(numVertex, INT_MAX);
    distance[src] = 0;

    while(!topo.empty())
    {
        int curr = topo.top();
        topo.pop();

        if(distance[curr] != INT_MAX)
        {
            for(auto it : adjList[curr])
            {
                if (distance[curr]+ it.second < distance[it.first])
                {
                    distance[it.first] = distance[curr]+ it.second;
                }
            }
        }
    }

    return distance;
}

int main()
{
    Graph g(6);

    g.addEdge(0,1,2);
    g.addEdge(0,4,1);
    g.addEdge(1,2,3);
    g.addEdge(2,3,6);
    g.addEdge(4,2,2);
    g.addEdge(4,5,4);
    g.addEdge(5,3,1);

    g.printAdjecencyList();

    int source = 0;

    cout<<"Shortest path from source "<<source<<": "<<endl;
    vector<int> path = g.shortestPathFromSource(source);
    for(int i = 0; i < path.size(); i++)
    {
        cout<<source<<" -> "<<i<<" : "<<path[i]<<endl;
    }

    cout<<endl;

    return 0;
}
