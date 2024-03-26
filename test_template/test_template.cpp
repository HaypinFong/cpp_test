#include<iostream>
#include<vector>
using namespace std;
class Type{
    public:
    void print(){
        cout<<"heihei"<<endl;
    }
};
template<typename T>
void callPrint(T obj){
    obj.print();
}
int main(int argc,char* argv[]){
    Type obj;
    callPrint(obj);
    vector<int> arr(3,1);
    arr.insert(arr.begin(),2,2);
    for(size_t i(0);i<arr.size();i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    return 0;
}