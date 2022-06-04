#include <iostream>
#include <vector>

using namespace std;

//Find the number of islands(1s)
/*
Input1:
grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Input2:
 grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
*/
//TC: O(N)    [O(5N) worst case a single node is traversed 5 times, 1 processing and 4 from side nodes.]
//SC: O(1)    [if recursive stack space is not considered.]
//SC: O(MxN)  [if recursive space is considered as there will be MxN recursive call.]
void markIslands(vector<vector<char>>&grid, int i, int j)
{
    if(i <0 || i >= grid.size() || j < 0 || j >= grid[i].size() || grid[i][j] != '1')
        return;

    grid[i][j] = '2';

    markIslands(grid, i-1, j);
    markIslands(grid, i+1, j);
    markIslands(grid, i, j-1);
    markIslands(grid, i, j+1);
}

int numIslands(vector<vector<char>>& grid)
{
    int numRows =grid.size();
    if(numRows == 0)
        return 0;

    int numColumns = grid[0].size(); //all rows have same number of column

    int numIslands = 0;

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numColumns; j++)
        {
            if(grid[i][j] == '1')
            {
                markIslands(grid, i, j);
                numIslands++;
            }
        }
    }

    return numIslands;
}

int main()
{
    vector<vector<char>> grid1 = {{'1','1','1','1','0'},
                                  {'1','1','0','1','0'},
                                  {'1','1','0','0','0'},
                                  {'0','0','0','0','0'}
                                 };

    vector<vector<char>> grid2 = {{'1','1','0','0','0'},
                                  {'1','1','0','0','0'},
                                  {'0','0','1','0','0'},
                                  {'0','0','0','1','1'}
                                 };

    cout<<"Num islands for grid1 = "<<numIslands(grid1)<<endl;
    cout<<"Num islands for grid2 = "<<numIslands(grid2)<<endl;

    return 0;
}
