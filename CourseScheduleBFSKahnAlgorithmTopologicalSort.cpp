#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Course Schedule - DFS(Recursive) Approach (TD)

/*
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true (You can finish the course)

Input graph:

  1 ---> 0


Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false (You can not finish the course)

Input graph:

      --->
    1      0
      <---
*/

//TC: O(V+E)
//SC: O(V)+O(V) ~ O(V) (for indegree array and BFS queue. Not considering adjacency list)

bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
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

    int count = 0;
    while(!q.empty())
    {
        auto curr = q.front();
        q.pop();
        count++;

        for(auto neighbour : adjList[curr])
        {
            nodeIndegree[neighbour]--;
            if(nodeIndegree[neighbour] == 0)
            {
                q.push(neighbour);
            }
        }
    }

    if(count == numCourses)
        return true;

    return false;
}

int main()
{
    int numCourses = 2;
    vector<vector<int>> input = {{1,0}};

    //int numCourses = 2;
    //vector<vector<int>> input = {{1,0}, {0,1}};

    if(canFinish(numCourses, input))
        cout<<"You can finish the course"<<endl;
    else
        cout<<"You can not finish the course"<<endl;

    return 0;
}
