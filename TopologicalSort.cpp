#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Depth First Search Traversal of Graph
/*
Input Directed Graph:

        5--->0<---4
        |         |
        |         |
        V         V
        2--->3--->1

Adjacency List graph:
Vertex[0]->
Vertex[1]->
Vertex[2]-> 3
Vertex[3]-> 1
Vertex[4]-> 0 1
Vertex[5]-> 0 2

Output:
Topological Sort =  5 4 2 3 1 0

*/

//TC: O(V + E)
//SC: O(V)+O(V) ~ O(V) (for visited array and stack)

class Graph{
public:
    Graph(int V)
    {
        numVertex = V;
        adjList = new vector<int>[numVertex];
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

    vector<int> topologicalSort()
    {
        vector<int> result;

        vector<int> visited(numVertex, 0);
        stack<int> topoStack;

        for(int i = 0; i < numVertex; i++)
        {
            if(visited[i] == 0)
            {
                topologicalSort(i, visited, topoStack);
            }
        }

        while(!topoStack.empty())
        {
            result.push_back(topoStack.top());
            topoStack.pop();
        }
        return result;
    }

    void topologicalSort(int node, vector<int>& visited, stack<int>& topoStack)
    {
        visited[node] = 1;

        for(auto neighbour : adjList[node])
        {
            if(visited[neighbour] == 0)
            {
                topologicalSort(neighbour, visited, topoStack);
            }
        }

        topoStack.push(node);
    }

private:
    int numVertex;
    vector<int>* adjList;
};

int main()
{
    Graph g(6);

    g.addEdge(5,0, true);
    g.addEdge(4,0, true);
    g.addEdge(5,2, true);
    g.addEdge(2,3, true);
    g.addEdge(3,1, true);
    g.addEdge(4,1, true);

    g.printAdjecencyList();

    cout<<"Topological Sort = ";
    vector<int> result = g.topologicalSort();
    for(auto val : result){
        cout<<val<<" ";
    }

    cout<<endl;

    return 0;
}
