#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//Breadth First Traversal of Graph
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
BFS Traversal = 0 1 2 3 7 5 4 6
*/

//TC: O(V+E)
//SC: O(V+E) + O(V) + O(V)  //queue and visited vector and not considering the result vector bfs

class Graph {
public:
	Graph(int V)
		: numVertices(V)
	{
        adjList = new vector<int>[numVertices];
	}

    vector<int> bfsTraversal()
    {
        vector<int> bfs;
        vector<int> visited(numVertices, 0);

        for (int i = 0; i < numVertices; i++)
        {
            if(!visited[i])
            {
                queue<int> q;
                q.push(i);
                visited[i] = 1;

                while(!q.empty())
                {
                    int node = q.front();
                    q.pop();

                    bfs.push_back(node);

                    for(auto neighbour : adjList[node])
                    {
                        if(!visited[neighbour])
                        {
                            q.push(neighbour);
                            visited[neighbour] = 1;
                        }
                    }
                }
            }
        }

        return bfs;
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
	int numVertices;
    vector<int> *adjList;
};

int main()
{
    Graph g(8);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 7);
    g.addEdge(3, 5);
    g.addEdge(5, 7);

    g.addEdge(4, 6);

    cout<<"Adjecency List graph:"<<endl;
    g.printAdjacencyList();

    vector<int> bfs = g.bfsTraversal();
    cout<<"BFS Traversal = ";
    for(int i = 0; i < bfs.size(); i++)
    {
        cout<<bfs[i]<<" ";
    }
    cout<<endl;

	return 0;
}
