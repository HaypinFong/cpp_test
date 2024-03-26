#include <iostream>
 
class Base1{
    public:
    int a;
    void print(){
        std::cout<<"base1::print()"<<std::endl;
    }
    static void print2(){
        std::cout<<"base1::print2()!!!"<<std::endl;
    }
};
 
typedef void(Base1::* pFunc1)();//定义指向普通成员函数的指针
typedef void(*pFunc2)();//定义指向静态成员函数的指针
 
 
int main(int argc,char * argv[])
{
    Base1 b;
    b.a=555;
    pFunc1 f1 = &(Base1::print);//获取普通成员函数的指针
    (b.*f1)();
    pFunc2 f2 = &(Base1::print2);//获取静态成员函数的指针
    f2();
 
}