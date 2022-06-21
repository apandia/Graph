#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Find Minimum Spanning Tree - Prims Algorithm
/*
Input Graph:

           2    3
        0----1----2
        |   /|   /
      6 | 8/ |5 / 7
        | /  | /
        3    4

Adjacency List graph:
Vertex[0]-> [1, 2] [3, 6]
Vertex[1]-> [0, 2] [2, 3] [3, 8] [4, 5]
Vertex[2]-> [1, 3] [4, 7]
Vertex[3]-> [0, 6] [1, 8]
Vertex[4]-> [1, 5] [2, 7]

Output:
Minimum Spanning Tree:
0->1
1->2
0->3
1->4
Total weight of MST = 16

           2    3
        0----1----2
        |    |
      6 |    |5
        |    |
        3    4

Total weight = 6+2+5+3 = 16
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
        for(int i = 0; i< numVertex; i++)
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

    void minimumSpanningTree();
    void minimumSpanningTreePQ();

private:
    int numVertex;
    vector<pair<int, int>>* adjList;
};

//Brute Force Approach
//TC : O(N^2)           [outer for loop for N-1 edge, inner for loop for finding min key)
//SC : O(N)+O(N)+O(N)   [key, parent, mst array, not considering adjacency list]
void Graph::minimumSpanningTree()
{
    vector<int> key(numVertex, INT_MAX);
    vector<int> parent(numVertex, -1);
    vector<bool> mst(numVertex, false);

    key[0] = 0;

    for(int i = 0; i < numVertex-1; i++)//N-1 edges in MST
    {
        int min = INT_MAX;
        int u;

        for(int v = 0; v < numVertex; v++)
        {
            if(mst[v] == false && key[v] < min)
            {
                min = key[v];
                u = v;
            }
        }

        mst[u] = true;

        for(auto it : adjList[u])
        {
            int v = it.first;
            int weight = it.second;

            if(mst[v] == false && weight < key[v])
            {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    for(int i = 1; i < numVertex; i++)
    {
        cout<<parent[i]<<"->"<<i<<endl;
    }

    int totalWeight = 0;
    for(auto val : key)
    {
        totalWeight += val;
    }

    cout<<"Total weight of MST = "<<totalWeight<<endl;
}

//MST using Min Priority Queue
//TC : O(N log N)       [outer for loop for N-1 edge, priority queue log N)
//SC : O(N)+O(N)+O(N)   [key, parent, mst array, not considering adjacency list]
void Graph::minimumSpanningTreePQ()
{
    vector<int> key(numVertex, INT_MAX);
    vector<bool> mst(numVertex, false);
    vector<int> parent(numVertex, -1);

    key[0] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;

    pq.push({0,0});

    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        mst[u] = true;

        for(auto it : adjList[u])
        {
            int v = it.first;
            int weight = it.second;

            if(mst[v] == false && weight < key[v])
            {
                parent[v] = u;
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }

    for(int i = 1; i < numVertex; i++)
    {
        cout<<parent[i]<<"->"<<i<<endl;
    }

    int totalWeight = 0;
    for(auto val : key)
    {
        totalWeight += val;
    }

    cout<<"Total weight of MST = "<<totalWeight<<endl;
}

int main()
{
    Graph g(5);

    g.addEdge(0,1,2);
    g.addEdge(0,3,6);
    g.addEdge(1,2,3);
    g.addEdge(1,3,8);
    g.addEdge(1,4,5);
    g.addEdge(2,4,7);

    g.printAdjecencyList();

    cout<<"Minimum Spanning Tree: "<<endl;
    g.minimumSpanningTree();

    cout<<endl;

    cout<<"Minimum Spanning Tree Using Priority Queue: "<<endl;
    g.minimumSpanningTreePQ();

    cout<<endl;

    return 0;
}
