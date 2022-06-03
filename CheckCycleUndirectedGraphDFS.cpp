#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//Check Cycle in Undirected Graph using DFS
/*
Input Graph:

        1 -- 2 -- 3      4 -- 6
             |    |
             |    |
             7 -- 5

Adjecency List graph:
Vertex 1 -> 2
Vertex 2 -> 1 3 7
Vertex 3 -> 2 5
Vertex 4 -> 6
Vertex 5 -> 3 7
Vertex 6 -> 4
Vertex 7 -> 2 5

Output: Cycle Present

*/

//TC: O(V+E)
//SC: O(V+E) + O(V) + O(V)  //queue and visited vector and not considering the result vector bfs

class Graph {
public:
	Graph(int V)
    {
        numVertices = V;
        adjList = new vector<int>[numVertices];
    }

    bool checkCycle(int node, int parent, vector<bool>& visited)
    {
        visited[node] = true;

        for(auto neighbour : adjList[node])
        {
            if(!visited[neighbour])
            {
                if(checkCycle(neighbour, parent, visited))
                {
                    return true;
                }
                else
                {
                    if(neighbour != parent)
                        return true;
                }
            }
        }
    }

    bool isCycle()
    {
        vector<bool> visited(numVertices, false);

        for (int i = 1; i < numVertices; i++)
        {
            if(!visited[i])
            {
                if(checkCycle(i, -1, visited))
                    return true;
            }
        }
    }

    void addEdge(int u, int v, bool directedGraph = false)
    {
        adjList[u].push_back(v);

        if(directedGraph == false)
            adjList[v].push_back(u);
    }

    void printAdjacencyList()
    {
        for (int i = 1; i < numVertices; i++)
        {
            cout<<"Vertex " <<i<<" -> ";
            for(int j = 0; j < adjList[i].size(); j++)
            {
                cout << adjList[i][j] << " ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

private:
    int numVertices;
    vector<int> *adjList;
};

int main()
{
    Graph g(8);

    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 7);
    g.addEdge(3, 5);
    g.addEdge(5, 7);

    g.addEdge(4, 6);

    if(g.isCycle())
        cout<<"Graph has Cycle"<<endl;
    else
        cout<<"Graph does not have cycle"<<endl;

    return 0;
}
