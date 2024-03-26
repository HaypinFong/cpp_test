#include<iostream>
#include<string>
using namespace std;
class A{
    public:
    A(string val){
        cout<<"calling A("<<val<<")"<<endl;
    }
    A& operator=(const A&) &{   //向可修改的左值赋值
        cout<<"calling A& operator=(const A&) &"<<endl;
        return *this;
    }
};
class B{
    public:
    B(string val){
        cout<<"calling B("<<val<<")"<<endl;
    }
    B& operator=(const B&) &&{  // 向右值赋值
        cout<<"calling B& operator=(const B&) &&"<<endl;
        return *this;
    }
};
int main(int argc,char *argv[]){
    A objA("1");
    objA = A("2");
    // A("7") = A("8");    // 尝试向右值赋值，error: no viable overloaded '='

    B("3") = B("4");
    B objB("5");
    // objB = B("6");  // 尝试向左值赋值，error: no viable overloaded '='
/*
calling A(1)
calling A(2)
calling A& operator=(const A&) &
calling B(4)
calling B(3)
calling B& operator-(const B&) &&
calling B(5)
*/
}