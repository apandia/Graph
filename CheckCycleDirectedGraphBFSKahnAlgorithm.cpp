#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Check cycle in a directed graph - BFS Using Kahn's Algorithm

/*
Input graph:

  0--->1--->2--->3--->4
            ^    |    |
            |    V    V
            7    6--->5
           //\
          /   \
        \/     \
        8------>9

Adjecancy List:
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
Cycle present in directed graph
*/

//TC: O(V+E) [2V -> processing/coloring node for undirectd graph ~V, E for adjecency list]
//SC: O(V)+O(V) ~ O(V) (for indegree array and queue)

class Graph {
public:
    Graph(int V)
    : numVertices(V)
    {
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

    bool checkCycle()
    {
        vector<int> nodeIndegree(numVertices, 0);
        for (int i = 0; i < numVertices; i++)
        {
            for(auto it : adjList[i])
                nodeIndegree[it]++;
        }

        queue<int> q;
        for (int i = 0; i < numVertices; i++)
        {
            if(nodeIndegree[i] == 0)
                q.push(i);
        }

        int count = 0;
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            count++;

            for(auto neighbour : adjList[node])
            {
                nodeIndegree[neighbour]--;
                if(nodeIndegree[neighbour] == 0)
                    q.push(neighbour);
            }
        }

        if(count == numVertices)
            return false;

        return true;
    }

private:
    int numVertices;
    vector<int> *adjList;
};

int main()
{
    Graph g(10);

    g.addEdge(0, 1, true);
    g.addEdge(1, 2, true);
    g.addEdge(2, 3, true);
    g.addEdge(3, 4, true);
    g.addEdge(3, 6, true);
    g.addEdge(4, 5, true);
    g.addEdge(6, 5, true);
    g.addEdge(7, 2, true);
    g.addEdge(7, 8, true);
    g.addEdge(8, 9, true);
    g.addEdge(9, 7, true);

    g.printAdjacencyList();

    if(g.checkCycle())
        cout<<"Cycle present in directed graph g"<<endl;
    else
        cout<<"Cycle not present in directed graph g"<<endl;

    return 0;
}
