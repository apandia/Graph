#include <iostream>
#include <cstring>

using namespace std;

//TC:  Adding a new vertex - O(V^2)
//     Removing a vertex - O(V^2)
//     Adding a new edge - O(1)
//     Removing an edge - O(1)
//     Query for edge - O(1)
//In order to add a new vertex to VxV matrix the storage must be increases to (|V|+1)^2.
//To achieve this we need to copy the whole matrix. Therefore the complexity is O(|V|^2).

//SC: O(V^2)  //Not feasible if size of V is greater i.e. 10^5
class Graph {
public:
	Graph(int V)
		: numVertices(V)
	{
		// Create a dynamic array of pointers. each pointer represent one row
		adjMatrix = new int* [numVertices];

		// Create a row for every pointer 
		for (int i = 0; i < numVertices; i++)
		{
			//For each rows create a array with required number of column 
			adjMatrix[i] = new int[numVertices];

			//initializes to 0
			memset(adjMatrix[i], 0, numVertices * sizeof(int));
		}
	}

	void addEdge(int u, int v)
	{
		adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
	}

	void printAdjacencyMatrix()
	{
		for (int i = 0; i < numVertices; i++)
		{
			for (int j = 0; j < numVertices; j++)
			{
				cout << adjMatrix[i][j] << " ";
			}
			cout << endl;
		}

	}

private:
	int numVertices;
	int** adjMatrix;
};

int main()
{
	Graph adjMatrixGraph(5);

	adjMatrixGraph.addEdge(0, 1);
	adjMatrixGraph.addEdge(1, 3);
	adjMatrixGraph.addEdge(2, 1);
	adjMatrixGraph.addEdge(3, 4);
	adjMatrixGraph.addEdge(4, 2);

	adjMatrixGraph.printAdjacencyMatrix();

	return 0;
}
