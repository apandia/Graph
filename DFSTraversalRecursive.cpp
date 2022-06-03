#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Depth First Search Traversal of Graph
/*
Input Graph:

   0 -- 1 -- 2 -- 3      4 -- 6
             |    |
             |    |
             7 -- 5

Adjecency List graph:
Vertex 0 -> 1
Vertex 1 -> 0 2
Vertex 2 -> 1 3 7
Vertex 3 -> 2 5
Vertex 4 -> 6
Vertex 5 -> 3 7
Vertex 6 -> 4
Vertex 7 -> 2 5

Output:
DFS Traversal = 0 1 2 3 5 7 4 6
DFS Traversal from node 0 = 0 1 2 3 5 7
DFS traversal from node 4 = 4 6
*/

//TC: O(V + E)
//SC: O(V) for visited array

class Graph{
public:
    Graph(int V)
    {
        numVertex = V;
        adjList = new vector<int>[numVertex];
    }

    void initializeVisited()
    {
        visited = new bool[numVertex];
        for (int i = 0; i < numVertex; i++)
            visited[i] = false;
    }

    void addEdge(int u, int v, bool isDirected = false)
    {
        adjList[u].push_back(v);
        if(!isDirected)
            adjList[v].push_back(u);
    }

    void printAdjecencyList()
    {
        for(int i =0; i< numVertex; i++)
        {
            cout<<"Vertex["<<i<<"]-> ";
            for(int j = 0; j < adjList[i].size(); j++)
            {
                cout<<adjList[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    void DFS()
    {
        initializeVisited();

        cout<<"DFS Traversal: "<<endl;
        for(int i = 0; i < numVertex; i++)
        {
            if(!visited[i])
            {
                DFSRecursive(i);
            }
        }
        cout<<endl;
    }

    void DFSRecursive(int node)
    {
        visited[node] = true;

        cout<<node<<" ";

        for(auto neighbour : adjList[node])
        {
            if(!visited[neighbour])
            {
                DFSRecursive(neighbour);
            }
        }
    }

private:
    int numVertex;
    vector<int>* adjList;
    bool* visited;
};

int main()
{
    Graph g(8);

    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(2,7);
    g.addEdge(3,5);
    g.addEdge(5,7);
    g.addEdge(4,6);

    g.printAdjecencyList();

    g.DFS();
    cout<<endl;

    g.initializeVisited();

    cout<<"DFS Traversal from node 0 = ";
    g.DFSRecursive(0);
    cout<<endl;

    g.initializeVisited();

    cout<<"DFS traversal from node 4 = ";
    g.DFSRecursive(4);
    cout<<endl;

	return 0;
}
