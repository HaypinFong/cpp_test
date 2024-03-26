#include<iostream>
#include<vector>
using namespace std;
void func(){
    vector<int> arr;
    cout<<( arr.begin()==arr.end() )<<endl;
    cout<<( arr.begin()==(arr.end()-1) )<<endl;
    arr.resize(3);
    cout<<( arr.begin()==(arr.end()-1) )<<endl;
}
void func2(){
    int arr[3]={3,1,4};
    cout<<arr[4]<<endl; // C数组不做下标越界检查
}
class Type
{
    public:
    Type(){
        cout<<"calling Type()"<<endl;
    }
    ~Type(){
        cout<<"calling ~Type()"<<endl;
    }
};
void func3(){
    vector<Type> arr(3);
    vector<Type*> parr(3);
    for(size_t i(0);i<arr.size();i++){
        parr[i] = &arr[i];
        cout<<parr[i]<<' '; // 0x1001054e0 0x1001054e1 0x1001054e2
    }
    cout<<endl;

    parr.resize(1); // 指针数组resize缩减不对size外指针做动作，内存空间保留
    for(size_t i(0);i<3;i++){
        cout<<parr[i]<<' '; // 0x1001054e0 0x1001054e1 0x1001054e2
    }
    cout<<endl;

    parr.resize(2); // 但是resize(2)后parr[1]被置零
    for(size_t i(0);i<3;i++){
        cout<<parr[i]<<' '; // 0x1001054e0 0x0 0x1001054e2
    }
    cout<<endl;

    parr.resize(3); // resize(3)后parr[1,2]被置零
    for(size_t i(0);i<3;i++){
        cout<<parr[i]<<' '; // 0x1001054e0 0x0 0x0
    }
    cout<<endl;

    cout<<arr.capacity()<<endl; // 3
    arr.resize(2);  // 对象数组resize缩减会析构掉最后一个对象，但内存空间保留
    cout<<arr.capacity()<<endl; // 3
    cout<<"breakpoint 0"<<endl;

    
}
void func4()
{
    vector<int> arr={3,1,4,1,5,9};
    vector<int> arr2;
    arr2.assign(arr.begin(),arr.end());
    for(int &i:arr2)
        cout<<i<<' ';
    cout<<endl;
}
int main(int argc,char *argv[]){
    // func();
    // func2();
    // func3();
    func4();
}