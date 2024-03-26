#include<iostream>
#include<string>
using namespace std;
class A{
    public:
    virtual void func(){
        cout<<"calling A::func()"<<endl;
    }
    protected:
    string a="A";
    private:
    string a_pri="A_pri";
};
class B:public A{
    public:
    virtual void funcB(){
        cout<<"calling B::funcB()"<<endl;
        a;
        // a_pri; // error: 'a_pri' is a private member of 'A'
    }
    void func(){
        cout<<"calling B::func()"<<endl;
    }
};
class C:public B{
    public:
    void func(){    // 派生类可以在它覆盖的函数前使用virtual关键字，但不是非得这么做，虚函数总是被继承为虚函数
        cout<<"calling C::func()"<<endl;
        /*如果基类把一个函数声明成虚函数func()，则该函数在派生类中默认地也是虚函数*/
        a;
    }
};

int main(int argc,char *argv[]){
    B *pobjB(new B());
    pobjB->func();
    delete pobjB;

    C *pobjC(new C());
    pobjC->func();
    pobjC->funcB();
    (*pobjC).func();
    C objC(*pobjC);
    objC.func();
    delete pobjC;
/*
calling A::func()
calling C::func()
calling B::funcB()
*/
}