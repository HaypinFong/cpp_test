#include<iostream>
#include<string>
using namespace std;
// 祖先类
class R{
    public:
    R():r("default"){
        cout<<"calling R()"<<endl;
    }
    R(string str):r(str){
        cout<<"calling R("<<str<<")"<<endl;
    }
    void print()const{cout<<"r="<<r<<endl;}
    private:
    string r;
};
// 父类A
class A:virtual public R{
    public:
    A(string str):R(str){
        cout<<"calling A("<<str<<")"<<endl;
    }
};
//父类B
class B:virtual public R{
    public:
    B(string str):R(str){
        cout<<"calling B("<<str<<")"<<endl;
    }
};

class C:public A,public B{  // 继承体系的拓扑结构：R,A,B，如果这里调换A与B的顺序则变成R,B,A
    public:
    C(string str1,string str2,string str3):A(str1),B(str2),R(str3){}
    /*
    派生关系：R->A，R->B，A,B->C
    1、在派生类C的构造函数初始化列表中通过间接基类A、B的构造函数初始化菱形基类R
    的数据成员是不得行的，尽管间接基类A与B的构造函数A(str1)和B(str2)均在各自
    的初始化列表中调用了菱形基类R的构造函数R(str)，但在这里虽然执行了A(str1)
    和B(str2)但均未调用各自的初始化列表中的R(str)部分，
    2、而是按照继承体系的拓扑结构R,A,B顺序分别调用了
    R(str3),A(str1)排除R(str),B(str2)排除R(str)，
    输出：
    calling R(str3)
    calling A(str1)
    calling B(str2)
    r=str3
    2、如果这里在派生类C的构造函数的初始化列表中不主动初始化菱形基类R则跟常规继承一样
    调用基类R的默认构造，将按照继承体系的拓扑结构R,A,B顺序分别调用
    R(),A(str1)排除R(str),B(str2)排除R(str)，
    输出：
    calling R()
    calling A(str1)
    calling B(str2)
    r=default
    */
};
int main(int argc,char * argv[]){
    C obj("str1","str2","str3");
    obj.print();
}