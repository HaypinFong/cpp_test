#include<iostream>
#include<string>
using namespace std;
// 看看不按继承关系初始化数据成员是否有影响？
// 派生类初始化列表的实际执行顺序是：
// 按继承顺序执行基类构造->按声明顺序执行派生类自身数据成员的构造
class A{
    public:
    string a;
    A(string val):a(val){
        cout<<"calling A(string)"<<endl;
    }
};
class B{
    public:
    string b;
    B(string val):b(val){
        cout<<"calling B(string)"<<endl;
    }
};
class C:public A{
    public:
    C(string vala,string b):objB(b),A(vala){}
    B objB;
};
int main(int argc,char *argv[]){
    C objC("aval","bval");
/*
calling A(string)
calling B(string
*/
}