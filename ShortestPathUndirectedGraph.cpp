#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Shortest path from source node in Undirected graph - BFS
/*
Input Directed Graph:

        1-----------2   7
      / |           |  /|
     0  |           | / |
      \ |           |/  |
        3---4---5---6---8

Adjacency List graph:
Vertex[0]-> 1 3
Vertex[1]-> 0 2 3
Vertex[2]-> 1 6
Vertex[3]-> 0 1 4
Vertex[4]-> 3 5
Vertex[5]-> 4 6
Vertex[6]-> 2 5 7 8
Vertex[7]-> 6 8
Vertex[8]-> 6 7

Output:
Shortest path from source 0:
0 -> 0 : 0
0 -> 1 : 1
0 -> 2 : 2
0 -> 3 : 1
0 -> 4 : 2
0 -> 5 : 3
0 -> 6 : 3
0 -> 7 : 4
0 -> 8 : 4
*/

//TC: O(V + E)
//SC: O(V)+O(V) [for queue and dist vector apart from adjacency list whose SC = O(V+E)]

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

    vector<int> shortestPathFromSource(int src)
    {
        vector<int> distance(numVertex, INT_MAX);

        queue<int> q;
        q.push(src);
        distance[src] = 0;

        while(!q.empty())
        {
            int curr = q.front();
            q.pop();

            for(auto neighbour : adjList[curr])
            {
                int newDistance = distance[curr]+1;
                if(newDistance < distance[neighbour])
                {
                    distance[neighbour] = newDistance;
                    q.push(neighbour);
                }
            }
        }
        return distance;
    }


private:
    int numVertex;
    vector<int>* adjList;
};

int main()
{
    Graph g(9);

    g.addEdge(0,1);
    g.addEdge(0,3);
    g.addEdge(1,2);
    g.addEdge(1,3);
    g.addEdge(2,6);
    g.addEdge(3,4);
    g.addEdge(4,5);
    g.addEdge(5,6);
    g.addEdge(6,7);
    g.addEdge(6,8);
    g.addEdge(7,8);

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
