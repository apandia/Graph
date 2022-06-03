#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Depth First Search Traversal of Graph
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
DFS Traversal = 0 1 2 3 5 7 4 6
DFS Traversal from node 0 = 0 1 2 3 5 7
DFS traversal from node 4 = 4 6
*/

//TC: O(V + E)
//SC: O(V)+O(~V) ~ O(V) (for visited array and stack.note stack will not store all at a single point)

class Graph{
public:
    Graph(int V)
    {
        numVertex = V;
        adjList = new vector<int>[numVertex];
    }

    void initializeVisited()
    {
        visited = new bool[numVertex];
        for (int i = 0; i < numVertex; i++)
            visited[i] = false;
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

    void DFS()
    {
        initializeVisited();

        for(int i = 0; i < numVertex; i++)
        {
            if(!visited[i])
            {
                DFSIterative(i);
            }
        }
        cout<<endl;
    }

    void DFSIterative(int node)
    {
        stack<int> st;
        st.push(node);

        while(!st.empty())
        {
            int n = st.top();
            st.pop();

            if(!visited[n])
            {
                visited[n] = true;
                cout<<n<<" ";

                for(auto neighbour : adjList[n])
                {
                    st.push(neighbour);
                }
            }
        }
    }

private:
    int numVertex;
    vector<int>* adjList;
    bool* visited;
};

int main()
{
    Graph g(8);

    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(2,7);
    g.addEdge(3,5);
    g.addEdge(5,7);
    g.addEdge(4,6);

    g.printAdjecencyList();

    cout<<"DFS Traversal (Iterative) = ";
    g.DFS();
    cout<<endl;

    cout<<"DFS Traversal(Iterative) from node 0 = ";
    g.initializeVisited();
    g.DFSIterative(0);
    cout<<endl;

    cout<<"DFS traversal(Iterative) from node 4 = ";
    g.initializeVisited();
    g.DFSIterative(4);
    cout<<endl;

	return 0;
}
