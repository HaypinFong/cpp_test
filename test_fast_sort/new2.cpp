#include<iostream>
/*
两个非负整数a,b,f(int a,int b)，输出a=123,b=456，a=0,b=1，
m*n矩阵，vector<vector<int>>，顺时针循转
*/
#include<vector>
using namespace std;
int** arr clock_roll(int **arr,int rows,int cols){
    //思路：转置后做列镜像，转置要生成中间矩阵，列镜像也可以不生成中间矩阵只换列下标
    int **arr_new = new int*[cols];
    for(int i(0);i<cols;i++) arr_new[i] = new int[rows];
    int **arr_trans = new int*[cols];
    for(int i(0);i<cols;i++) arr_trans[i] = new int[rows];
    // 先转置
    for(int i(0);i<cols;i++){
        for(int j(0);j<rows;j++){
            arr_trans[i][j] = arr[j][i];
        }
    }
    // 后列镜像
    for(int i(0);i<cols;i++){
        for(int j(0);j<rows;j++){
            arr_new[i][j] = arr_trans[i][cols-j-1]; // 
        }
    }
    // 释放arr_trans
    for(int i(0);i<cols;i++) delete [] arr_trans[i];
    delete arr_trans;
    // 记得释放内存
    return arr_new;

    // 2
}