#include<iostream>
#include<vector>
using namespace std;
template<typename T>
void print(vector<T> arr)
{
    for(T &i:arr)
        cout<<i<<' ';
    cout<<endl;
}
int main(int argc,char **argv)
{
    vector<int> myarr(3,12);
    print(myarr);
    myarr.insert(myarr.end(),2,24);
    print(myarr);
}