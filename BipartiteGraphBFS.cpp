#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Check if graph is bipartite i.e
//  1.can be color with exactly 2 color
//  2.no 2 neighbour can have same color

//Obeservation: Graph is normally not bipartite if there odd number of nodes in cycle

/*
Input Graph1:

                3---4
               /    |
          1---2     |
               \    |
                8---5---6---7

Output: Graph g1 is not bipartite

Input Graph2:


              3-------4
             /        |
         1--2         |
             \        |
              7---6---5--8



Output: Graph g2is bipartite
*/
//TC: O(V+E)
//SC: O(V+E) + O(V) + O(V)
//      O(V+E)  - Adjecency list
//      O(V)    - color array
//      O(V)    - queue to hold nodes
class Graph{
public:
    Graph(int V)
    {
        numVertex = V;
        adjList = new vector<int>[numVertex];
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printAdjList()
    {
        for(int i = 1; i < numVertex; i++)
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

    bool checkBipartite()
    {
        vector<int> nodeColor(numVertex, -1);

        for(int i = 1; i < numVertex; i++)
        {
            if(nodeColor[i] == -1)
            {
                //Anytime false is returned, we can return false and no need to process further
                if(!checkBipartiteBFS(i, nodeColor))
                    return false;
            }
        }
        return true;
    }

    bool checkBipartiteBFS(int node, vector<int>& nodeColor)
    {
        queue<int> q;
        q.push(node);
        nodeColor[node] = 1;

        while(!q.empty())
        {
            int currNode = q.front();
            q.pop();

            for(auto neighbour : adjList[currNode])
            {
                if(nodeColor[neighbour] == -1)
                {
                    nodeColor[neighbour] = 1 - nodeColor[currNode];
                    q.push(neighbour);
                }
                else
                {
                    if(nodeColor[currNode] == nodeColor[neighbour])
                        return false;
                }
            }
        }
        return true;
    }

private:
    int numVertex;
    vector<int>* adjList;
};

int main()
{
    Graph g1(9);

    g1.addEdge(1,2);
    g1.addEdge(2,3);
    g1.addEdge(2,8);
    g1.addEdge(3,4);
    g1.addEdge(4,5);
    g1.addEdge(5,6);
    g1.addEdge(5,8);
    g1.addEdge(6,7);

    cout<<"Adjecency List of g1 = "<<endl;
    g1.printAdjList();

    if(g1.checkBipartite())
        cout<<"Graph g1 is bipartite"<<endl;
    else
        cout<<"Graph g1 is not bipartite"<<endl;

    Graph g2(9);
    g2.addEdge(1,2);
    g2.addEdge(2,3);
    g2.addEdge(2,7);
    g2.addEdge(3,4);
    g2.addEdge(4,5);
    g2.addEdge(5,6);
    g2.addEdge(5,8);
    g2.addEdge(6,7);

    cout<<endl;
    cout<<"Adjecency List of g2 = "<<endl;
    g2.printAdjList();

    if(g2.checkBipartite())
        cout<<"Graph g2 is bipartite"<<endl;
    else
        cout<<"Graph g2 is not bipartite"<<endl;

    return 0;
}
