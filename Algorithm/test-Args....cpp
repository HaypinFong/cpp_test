#include<iostream>
#include<typeinfo>
using namespace std;
template<typename T>
void func(T arg)
{
    cout<<typeid(T).name()<<' ';
}
template<typename T,typename ... Args>
void func(T arg1,Args ... args)
{
    cout<<typeid(T).name()<<' ';
    func(args...);
}
int main(int argc,char* argv[])
{
    func(1,'a',"haha",3.14,1e10,LONG_MAX);
    cout<<endl;
}