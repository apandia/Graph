#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//Possible Bipartition - split group by bipartite approach - BFS

/*
Input1:
n = 4, dislikes = [[1,2],[1,3],[2,4]]
Output: true
Explanation: group1 [1,4] and group2 [2,3].

Input2:
n = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
Output: false
*/

//TC: O(V+E) [2V -> processing/coloring node for undirectd graph ~V, E for adjecency list]
//SC: O(V+E) + O(V) + O(V)

bool isBiPartite(int node, vector<vector<int>>& adjList, vector<int>& nodeColor)
{
    queue<int> q;
    q.push(node);

    nodeColor[node] = 1;

    while(!q.empty())
    {
        int curr = q.front();
        q.pop();

        for(auto neighbour : adjList[curr])
        {
            if(nodeColor[neighbour] == -1)
            {
                q.push(neighbour);
                nodeColor[neighbour] = 1-nodeColor[curr];
            }
            else
            {
                if(nodeColor[curr] == nodeColor[neighbour]) //oddcycle case
                    return false;
            }
        }
    }
    return true;
}

bool possibleBipartition(int n, vector<vector<int>>& dislikes)
{
    vector<vector<int>> adjList(n+1);
    for(int i = 0; i < dislikes.size(); i++)
    {
        adjList[dislikes[i][0]].push_back(dislikes[i][1]);
        adjList[dislikes[i][1]].push_back(dislikes[i][0]);
    }

    vector<int> nodeColor(n+1, -1);

    for(int i = 1; i <= n; i++)
    {
        if(nodeColor[i] == -1)
        {
            if(!isBiPartite(i, adjList, nodeColor))
                return false;
        }
    }
    return true;
}

int main()
{
    vector<vector<int>> group1 = {{1,2},
                                  {1,3},
                                  {2,4}
                                 };

    vector<vector<int>> group2 = {{1,2},
                                  {2,3},
                                  {3,4},
                                  {4,5},
                                  {1,5}
                                 };

    if(possibleBipartition(4, group1))
        cout<<"Split possible for group1"<<endl;
    else
        cout<<"Split not possible for group1"<<endl;

    if(possibleBipartition(5, group2))
        cout<<"Split possible for group2"<<endl;
    else
        cout<<"Split not possible for group2"<<endl;

    return 0;
}
