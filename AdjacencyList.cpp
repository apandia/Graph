#include <iostream>
#include <vector>

using namespace std;

//Adjecency list for graph representation
/*
Input Graph:

        0 -- 1 -- 2 -- 4
             | \  |  /
             |  \ | /
             5 -- 3

Output:
Adjecency List for Non directed graph:
Vertex 0 -> 1
Vertex 1 -> 0 2 3 5
Vertex 2 -> 1 4 3
Vertex 3 -> 1 2 4 5
Vertex 4 -> 2 3
Vertex 5 -> 1 3

Adjecency List for Non directed graph:
Vertex 0 -> 1
Vertex 1 -> 2 3 5
Vertex 2 -> 4 3
Vertex 3 -> 4 5
Vertex 4 ->
Vertex 5 ->
*/

//TC:  Adding a new vertex - O(1)
//     Removing a vertex - O(V+E)
//     Adding a new edge - O(1)
//     Removing an edge - O(E)
//     Query for edge - O(V)
//SC: O(V+2E) //for directed graph. edge for both u and v syored for directed graph
//SC: O(V+E)  //for non directed graph

//There are two pointers in adjacency list first points to the front node and the other
//one points to the rear node.Thus insertion of a vertex can be done directly in O(1) time.

//In order to remove a vertex, we need to search for the vertex which will require O(|V|) time
//in worst case, after this we need to traverse the edges and in worst case it will require O(|E|) time.
//Hence, total time complexity is O(|V|+|E|).

//In an adjacency list every vertex is associated with a list of adjacent vertices. For a given graph, in
//order to check for an edge we need to check for vertices adjacent to given vertex.A vertex can have at most O(|V|)
//neighbours and in worst can we would have to check for every adjacent vertex. Therefore, time complexity is O(|V|)
class Graph {
public:
	Graph(int V)
		: numVertices(V)
	{
        adjList = new vector<int>[V];
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
    }

private:
	int numVertices;
    vector<int> *adjList;
};

int main()
{
    Graph adjListGraph(6);

    adjListGraph.addEdge(0, 1);
	adjListGraph.addEdge(1, 2);
	adjListGraph.addEdge(1, 3);
    adjListGraph.addEdge(1, 5);
    adjListGraph.addEdge(2, 4);
    adjListGraph.addEdge(2, 3);
    adjListGraph.addEdge(3, 4);
    adjListGraph.addEdge(3, 5);

    cout<<"Adjecency List for Non directed graph:"<<endl;
	adjListGraph.printAdjacencyList();

    cout<<"Adjecency List for Non directed graph:"<<endl;
    Graph adjListGraphDirected(6);

    adjListGraphDirected.addEdge(0, 1, true);
    adjListGraphDirected.addEdge(1, 2, true);
    adjListGraphDirected.addEdge(1, 3, true);
    adjListGraphDirected.addEdge(1, 5, true);
    adjListGraphDirected.addEdge(2, 4, true);
    adjListGraphDirected.addEdge(2, 3, true);
    adjListGraphDirected.addEdge(3, 4, true);
    adjListGraphDirected.addEdge(3, 5, true);

    adjListGraphDirected.printAdjacencyList();

	return 0;
}
