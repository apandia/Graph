#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Topological sort BFS - kahn's Algorithm
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
Topological Sort =  5 4 0 2 3 1

*/

//TC: O(V + E)
//SC: O(V)+O(V) ~ O(V) (for indegree array and queue)

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
        vector<int> topo;
        queue<int> q;

        vector<int> nodeIndegree(numVertex, 0);

        for(int i = 0; i < numVertex; i++)
        {
            for(auto it : adjList[i])
            {
                nodeIndegree[it]++;
            }
        }

        for(int i = 0; i < numVertex; i++)
        {
            if(nodeIndegree[i] == 0)
                q.push(i);
        }

        while(!q.empty())
        {
            int node = q.front();
            q.pop();

            topo.push_back(node);

            for(auto neighbour : adjList[node])
            {
                nodeIndegree[neighbour]--;
                if(nodeIndegree[neighbour] == 0)
                    q.push(neighbour);
            }
        }

        return topo;
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
