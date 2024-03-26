#include<iostream>
#include<vector>
using namespace std;
int find_grid_len(vector<vector<int> >arr,int rows,int cols){
    //grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
    // 思路：上下左右
    int len(0);
    if(rows<2){
        // 只有一行
        for(int icol(0);icol<cols;icol++){
            if(arr[0][icol]==1)
                len+=2;
        }
        len += 2;
        return len;
    }
    if(cols<2){
        // 只有一列
        for(int irow(0);irow<rows;irow++){
            if(arr[irow][0]==1)
                len+=2;
        }
        len += 2;
        return len;
    }
    // 多于一行且多于一列的
    for(int irow(0);irow<rows;irow++){
        for(int icol(0);icol<cols;icol++){
            if(arr[irow][icol]==0)
                continue;
            // 先考虑上下
            if(irow==0)
                len += (2-arr[irow+1][icol]);
            else if(irow==rows-1)
                len += (2-arr[irow-1][icol]);
            else
                len += (2-arr[irow-1][icol]-arr[irow+1][icol]);
            // 再考虑左右
            if(icol == 0)
                len += (2-arr[irow][icol+1]);
            else if(icol == cols-1)
                len += (2-arr[irow][icol-1]);
            else
                len += (2-arr[irow][icol+1]-arr[irow][icol-1]);
        }
    }
    return len;
}
int main(int argc,char **argv){
    vector<vector<int> > grid{4,vector<int>(4)};
    grid[0][0] = 0;grid[0][1] = 1;grid[0][2] = 0;grid[0][3] = 0;
    grid[1][0] = 1;grid[1][1] = 1;grid[1][2] = 1;grid[1][3] = 0;
    grid[2][0] = 0;grid[2][1] = 1;grid[2][2] = 0;grid[2][3] = 0;
    grid[3][0] = 1;grid[3][1] = 1;grid[3][2] = 0;grid[3][3] = 0;
    // [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
    cout<<find_grid_len(grid,4,4)<<endl;
    vector<vector<int> > grid2{1,vector<int>(1)};
    grid2[0][0] = 1;
    cout<<find_grid_len(grid2,1,1)<<endl;
    vector<vector<int> > grid3{1,vector<int>(2)};
    grid3[0][0] = 1;grid3[0][1] = 0;
    cout<<find_grid_len(grid3,1,2)<<endl;
}