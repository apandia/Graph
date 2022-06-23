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
Articulation Point: 1
*/

//TC: O(V+E)
//SC: O(V) + O(V)  //For timeOfInsertion and low array and not considering dfs related space i.e visited array and adjacency list

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

    void dfs(int node, int parent, int counter, vector<int>& timeOfInsertion, vector<int>& lowestTimeOfInsertion, vector<int>& visited, vector<int>& result)
    {
        visited[node] = 1;
        timeOfInsertion[node] = lowestTimeOfInsertion[node] = counter++;

        int child = 0;

        for(auto neighbour : adjList[node])
        {
            if(neighbour == parent)
                continue;

            if(visited[neighbour] == 0)
            {
                dfs(neighbour, node, counter, timeOfInsertion, lowestTimeOfInsertion, visited, result);
                lowestTimeOfInsertion[node] = min(lowestTimeOfInsertion[node], lowestTimeOfInsertion[neighbour]);
                if((lowestTimeOfInsertion[neighbour] >= timeOfInsertion[node]) && (parent != -1))
                {
                    result[node] = 1;
                }
                child++;
            }
            else
            {
                lowestTimeOfInsertion[node] = min(lowestTimeOfInsertion[node], timeOfInsertion[neighbour]);
            }
        }

        if(parent == -1 && child > 1)
        {
            result[node] = 1;
        }
    }

    vector<int> articulationPoint()
    {
        vector<int> result(numVertices, 0);

        vector<int> timeOfInsertion(numVertices, -1);
        vector<int> lowestTimeOfInsertion(numVertices, -1);
        vector<int> visited(numVertices, 0);

        int counter = 0;

        for(int i = 0; i < numVertices; i++)
        {
            if(visited[i] == 0)
            {
                dfs(i, -1, counter, timeOfInsertion, lowestTimeOfInsertion, visited, result);
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

    cout<<"Articulation Point: ";
    vector<int> ap = g.articulationPoint();
    for(int i = 0; i < ap.size(); i++)
    {
        if(ap[i] == 1)
        {
            cout<<ap[i]<<" ";
        }
    }
    cout<<endl;

    return 0;
}
