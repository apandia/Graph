#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// Course Schedule2 - BFS using Kahn Algorithm for topological sort

/*
Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3] (or [0,1,2,3] is also correct)

Input graph:

             1--->0
             ^    ^
             |    |
             3--->2
*/

//TC: O(V+E)
//SC: O(V)+O(V) ~ O(V) (for indegree array and BFS queue. Not considering adjacency list)

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
{
    vector<vector<int>> adjList(numCourses);

    for(int i =0; i < prerequisites.size(); i++) {
        adjList[prerequisites[i][0]].push_back(prerequisites[i][1]);
    }

    vector<int> nodeIndegree(numCourses, 0);
    for(int i = 0; i < numCourses; i++)
    {
        for(auto it : adjList[i])
        {
            nodeIndegree[it]++;
        }
    }

    queue<int> q;
    for(int i = 0; i < nodeIndegree.size(); i++)
    {
        if(nodeIndegree[i] == 0)
        {
            q.push(i);
        }
    }

    stack<int> topo;
    while(!q.empty())
    {
        auto curr = q.front();
        q.pop();

        topo.push(curr);

        for(auto neighbour : adjList[curr])
        {
            nodeIndegree[neighbour]--;
            if(nodeIndegree[neighbour] == 0)
            {
                q.push(neighbour);
            }
        }
    }

    vector<int> result;

    while(!topo.empty())
    {
        result.push_back(topo.top());
        topo.pop();
    }

    return result;
}

int main()
{
    int numCourses = 4;
    vector<vector<int>> input = {{1,0},
                                 {2,0},
                                 {3,1},
                                 {3,2}
                                };

    vector<int> courseOrder = findOrder(numCourses, input);

    cout<<"The order in which course can be taken: [";
    for(auto course : courseOrder)
        cout<< course <<" ";

    cout<<"]"<<endl;

    return 0;
}
