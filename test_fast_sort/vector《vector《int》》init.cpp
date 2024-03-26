#include<iostream>
#include<vector>
using namespace std;
int main(int argc,char **argv){
    vector<int> arr0({1,2,3,4,5});
    for(int i(0);i<arr0.size();i++)
        cout<<arr0[i]<<' ';
    cout<<endl;

    vector<vector<int> >arr({{1,2,3},{4,5,6,7}}); // 多维数组初始化
    for(int i(0);i<arr.size();i++){
        for(int j(0);j<arr[i].size();j++)
            cout<<arr[i][j]<<' ';
        cout<<endl;
    }
    cout<<endl;
}