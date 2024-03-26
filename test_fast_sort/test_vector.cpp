#include <vector>
#include <iostream>
using namespace std;
int main(int argc,char* argv[])
{
    vector<int> arr = {3,1,4,1,5,9,2,6};
    vector<vector<int>::iterator> ites(arr.size());
    int i = 0;
    for(vector<int>::iterator ite = arr.begin();ite!=arr.end();ite++,i++)
    {
        cout<<*ite<<' ';
        ites[i] = ite;
    }
    arr.erase(++arr.begin());
    cout<<endl;
    for(auto i:ites)
        cout<<*i<<' ';
    cout<<endl;
}