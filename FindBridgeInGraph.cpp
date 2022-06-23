#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//Find bridge (critical connection) in graph
/*
Input Graph:
                2
               /|
              / |
             1  |
             |\ |
             | \|
             |  0
             |
             3


Adjecency List graph:
Vertex 0 -> 1 2
Vertex 1 -> 0 2 3
Vertex 2 -> 0 1
Vertex 3 -> 1

Output:
Critical Connection:
1-3 [or 3-1]
*/

//TC: O(V+E)
//SC: O(V) + O(V)  //For timeToInsert and low array and not considering dfs related space i.e visited array and adjacency list

class Graph {
public:
	Graph(int V)
    {
        numVertices = V;
        adjList = new vector<int>[numVertices];
    }

    void addEdge(int u, int v, bool directedGraph = false)
    {
        adjList[u].push_back(v);

        if(directedGraph == false)
            adjList[v].push_back(u);
    }

    void printAdjacencyList()
    {
        for (int i = 0; i < numVertices; i++)
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

    void dfs(int node, int parent, int counter, vector<int>& timeToInsert, vector<int>& low, vector<int>& visited, vector<vector<int>>& result)
    {
        visited[node] = 1;
        timeToInsert[node] = low[node] = counter++;

        for(auto neighbour : adjList[node])
        {
            if(neighbour == parent)
                continue;

            if(visited[neighbour] == 0)
            {
                dfs(neighbour, node, counter, timeToInsert, low, visited, result);

                //Once come back from dfs(from neighbour back to node),
                //check the low value of its neighbour adjacent and update if needed
                //Note: low value of is neighbour may have been updated in the else case of visited check
                low[node] = min(low[node], low[neighbour]);

                //Rule to find bridge
                if(low[neighbour] > timeToInsert[node])
                {
                    result.push_back({node, neighbour});
                }
            }
            else
            {
                low[node] = min(low[node], timeToInsert[neighbour]);
            }
        }
    }

    vector<vector<int>> criticalConnections()
    {
        vector<vector<int>> result;

        vector<int> timeToInsert(numVertices, -1);  //time of insertion/traversal
        vector<int> low(numVertices, -1);           //lowest time of insertion/traversal among all its adjacents/neighbours
        vector<int> visited(numVertices, 0);

        int counter = 0;

        for(int i = 0; i < numVertices; i++)
        {
            if(visited[i] == 0)
            {
                dfs(i, -1, counter, timeToInsert, low, visited, result);
            }
        }
        return result;
    }

private:
    int numVertices;
    vector<int> *adjList;
};

int main()
{
    Graph g(4);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    g.printAdjacencyList();

    cout<<"Critical Connection: "<<endl;
    vector<vector<int>> cc = g.criticalConnections();
    for(int i = 0; i < cc.size(); i++)
    {
        for(int j = 0; j < cc[i].size(); j++)
        {
            cout<<cc[i][j];
            if(j != cc[i].size()-1)
                cout<<"-";
        }
        cout<<endl;
    }

    return 0;
}
