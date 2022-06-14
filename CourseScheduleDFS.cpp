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
//SC: O(V+E) + O(V)  [for adjecency list and for visited array]

bool checkCycle(int node, vector<int>& visited, vector<vector<int>>& adjList)
{
    if(visited[node] == 2)
        return true;

    visited[node] = 2;

    for(auto neighbour : adjList[node])
    {
        if(visited[neighbour] != 1)
        {
            if(checkCycle(neighbour, visited, adjList))
                return true;
        }
    }

    visited[node] = 1;
    return false;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
{
    vector<vector<int>> adjList(numCourses+1);

    for(int i =0; i < prerequisites.size(); i++) {
        adjList[prerequisites[i][0]].push_back(prerequisites[i][1]);
    }

    vector<int> visited(numCourses+1, 0);

    for(int i = 0; i <= numCourses; i++)
    {
        if(visited[i] == 0)
        {
            if(checkCycle(i, visited, adjList))
                return false;
        }
    }
    return true;
}

int main()
{
    //int numCourses = 2;
    //vector<vector<int>> input = {{1,0}};

    int numCourses = 2;
    vector<vector<int>> input = {{1,0}, {0,1}};

    if(canFinish(numCourses, input))
        cout<<"You can finish the course"<<endl;
    else
        cout<<"You can not finish the course"<<endl;

    return 0;
}
