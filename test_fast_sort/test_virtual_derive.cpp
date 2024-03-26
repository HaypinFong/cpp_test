#include<iostream>
using namespace std;
class A{
    // int m_numA;
    // void func(){
    //     cout<<"calling func()"<<endl;
    // }
    // void func2(){
    //     cout<<"calling func2()"<<endl;
    // }
    public:
    virtual void funcA()
    {   // 基类的虚函数必须予以实现！以防派生类未实现虚函数时还可以调用到基类虚函数
        // 虚函数既使不调用也必须予以实现
        cout<<"calling A::funcA()"<<endl;
    }
};
class B{
    public:
    // int m_numB;
    virtual void funcB()
    {
        cout<<"calling B::funcB()"<<endl;
    }
    ;
};
class C:public A
        ,public B
        {
    
};
class D:public A{
    public:
    // void funcA(){
    //     cout<<"calling D::funcA()"<<endl;
    // }
    // void funcA() override{
    //     cout<<"calling D::funcA() override"<<endl;
    // }
};
int main(int argc,char *argv[]){
    // https://blog.csdn.net/RainVictor1/article/details/76100546
    // 类对象大小不能为空，空类实例大小为1，sizeof(Type)=非静态数据成员大小+虚指针+字节对齐
    cout<<"sizeof(A): "<<sizeof(A)<<endl;
    cout<<"sizeof(C): "<<sizeof(C)<<endl;
    A objA;
    C objC;
    cout<<"sizeof(objA): "<<sizeof(objA)<<endl;
    cout<<"sizeof(objC): "<<sizeof(objC)<<endl;
    // 虚函数表指针vptr以基类为单位，一个基类一个vptr，两个基类两个vptr，虚表指针存储在实例中
    A objA2;
    objA2.funcA();
    D objD;
    objD.funcA();
    A* pA(&objD);
    pA->funcA();

    C objC2;
    // objC2.funcB();
}