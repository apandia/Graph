#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Check cycle in a directed graph - DFS

/*
Input graph1:
Vertex 1 -> 2
Vertex 2 -> 3
Vertex 3 -> 4 6
Vertex 4 -> 5
Vertex 5 ->
Vertex 6 -> 5
Vertex 7 -> 2 8
Vertex 8 -> 9
Vertex 9 -> 7

Output:
Cycle present in directed graph g1

Input graph2:
Vertex 1 -> 0

Output:
Cycle not present in directed graph g2

Input graph3:
Vertex 0 -> 1
Vertex 1 -> 0

Output:
Cycle present in directed graph g3

*/

//TC: O(V+E) [2V -> processing/coloring node for undirectd graph ~V, E for adjecency list]
//SC: O(V+E) + O(V) + O(V)  [for adjecency list and for 2 visited array]


class Graph {
public:
    Graph(int V)
    : numVertices(V)
    {
        adjList = new vector<int>[numVertices];
    }

    bool checkCycle()
    {
        vector<bool> visited(numVertices, false);
        vector<bool> dfsVisited(numVertices, false);

        for (int i = 1; i < numVertices; i++)
        {
            if(!visited[i])
            {
                if(checkCycleDFS(i, visited, dfsVisited))
                    return true;
            }
        }
        return false;
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

private:
    bool checkCycleDFS(int node, vector<bool>& visited, vector<bool>& dfsVisited)
    {
        visited[node] = true;
        dfsVisited[node] = true;

        for(int neighbour : adjList[node])
        {
            if(!visited[neighbour])
            {
                if(checkCycleDFS(neighbour, visited, dfsVisited))
                    return true;
            }
            else
            {
                if(dfsVisited[neighbour])
                    return true;
            }
        }
        dfsVisited[node] = false;
        return false;
    }

private:
    int numVertices;
    vector<int> *adjList;
};

int main()
{
    Graph g1(10);

    g1.addEdge(1, 2, true);
    g1.addEdge(2, 3, true);
    g1.addEdge(3, 4, true);
    g1.addEdge(3, 6, true);
    g1.addEdge(4, 5, true);
    g1.addEdge(6, 5, true);
    g1.addEdge(7, 2, true);
    g1.addEdge(7, 8, true);
    g1.addEdge(8, 9, true);
    g1.addEdge(9, 7, true);

    g1.printAdjacencyList();

    if(g1.checkCycle())
        cout<<"Cycle present in directed graph g1"<<endl;
    else
        cout<<"Cycle not present in directed graph g1"<<endl;

    cout<<endl;

    Graph g2(2);
    g2.addEdge(1, 0, true);

    g2.printAdjacencyList();

    if(g2.checkCycle())
        cout<<"Cycle present in directed graph g2"<<endl;
    else
        cout<<"Cycle not present in directed graph g2"<<endl;

    cout<<endl;

    Graph g3(2);
    g3.addEdge(1, 0, true);
    g3.addEdge(0, 1, true);

    g3.printAdjacencyList();

    if(g3.checkCycle())
        cout<<"Cycle present in directed graph g3"<<endl;
    else
        cout<<"Cycle not present in directed graph g3"<<endl;

    cout<<endl;

    return 0;
}
