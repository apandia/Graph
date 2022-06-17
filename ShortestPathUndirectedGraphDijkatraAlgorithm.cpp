#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Shortest path from source node in undirected weighted graph - Dijkatra Algorithm
/*
Input Graph:

           2      5
        1------2----5
        |      |   /
      1 |     4|  / 1
        |      | /
        4------3
           3

Adjacency List graph:
Vertex[1]-> [2, 2] [4, 1]
Vertex[2]-> [1, 2] [3, 4] [5, 5]
Vertex[3]-> [2, 4] [4, 3] [5, 1]
Vertex[4]-> [1, 1] [3, 3]
Vertex[5]-> [2, 5] [3, 1]


Output:
Shortest path from source 1:
Shortest path from source 1:
1 -> 1 : 0
1 -> 2 : 2
1 -> 3 : 4
1 -> 4 : 1
1 -> 5 : 5

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
        adjList[v].push_back({u, w});
    }

    void printAdjecencyList()
    {
        for(int i = 1; i< numVertex; i++)
        {
            cout<<"Vertex["<<i<<"]-> ";
            for(auto it : adjList[i])
            {
                cout<<"["<<it.first<<", "<<it.second<<"] ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    vector<int> shortestPathFromSource(int src);

private:
    int numVertex;
    vector<pair<int, int>>* adjList;
};

//TC : O(N+E)*log N ~ O(N log N)    [log N for priority queue]
//SC : O(N) + O(N)                  [Not considering space for Adjacency list which is O(N+E]
vector<int> Graph::shortestPathFromSource(int src)
{
    vector<int> distanceTo(numVertex, INT_MAX);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;

    distanceTo[src] = 0;
    pq.push({0,src});

    while(!pq.empty())
    {
        int prevNodeDistance = pq.top().first;
        int prevNode = pq.top().second;
        pq.pop();

        for(auto it : adjList[prevNode])
        {
            int currNode = it.first;
            int currNodeDistance = it.second;

            if(prevNodeDistance + currNodeDistance < distanceTo[currNode])
            {
                distanceTo[currNode] = prevNodeDistance + currNodeDistance;
                pq.push({distanceTo[currNode], currNode});
            }
        }
    }

    return distanceTo;
}

int main()
{
    Graph g(6);

    g.addEdge(1,2,2);
    g.addEdge(1,4,1);
    g.addEdge(2,3,4);
    g.addEdge(2,5,5);
    g.addEdge(3,4,3);
    g.addEdge(3,5,1);

    g.printAdjecencyList();

    int source = 1;

    cout<<"Shortest path from source "<<source<<": "<<endl;
    vector<int> path = g.shortestPathFromSource(source);
    for(int i = 1; i < path.size(); i++)
    {
        cout<<source<<" -> "<<i<<" : "<<path[i]<<endl;
    }

    cout<<endl;

    return 0;
}
