#include<iostream>
using namespace std;
class Base
{
    public:
    //virtual Base(){};   // constructor cannot be declared 'virtual'，必须先将实例构造完，才能索引实例的虚函数表指针动态查找虚函数
    Base(){cout<<"calling Base::Base()"<<endl;}
    virtual void method(){cout<<"calling Base::method()"<<endl;}
    virtual ~Base(){cout<<"calling Base::~Base()"<<endl;}
};
class Derived: public Base
{
    public:
    Derived(){cout<<"calling Derived::Derived()"<<endl;}
    virtual void method(){cout<<"calling Derived::method()"<<endl;}
    virtual ~Derived(){cout<<"calling Derived::~Derived()"<<endl;}
};
class Derived2: public Derived
{
    public:
    Derived2(){cout<<"calling Derived2::Derived2()"<<endl;}
    //virtual void method(){cout<<"calling Derived2::method()"<<endl;}
    virtual ~Derived2(){cout<<"calling Derived2::~Derived2()"<<endl;}
};
int main(int argc,char* argv[])
{
    Base* pb = new Derived2();   // 从里到外构造
    pb->method();               // 一般虚函数，从Derived2到Base从外到里查找，先找到哪个调用哪个，calling Derived::method()
    delete pb;                  // 从外到里析构，先调用派生类的虚析构函数，再调用基类的
    cout<<"----------1----------"<<endl;
    Derived* pb2 = new Derived2();
    pb2->method();              // 从Derived2到Derived从外到里查找，calling Derived::method()
    delete pb2;
}