#include"template1.h"
#include<iostream>
using namespace std;

extern template void func_template<int>(int obj);   // 显式实例化模板函数声明

extern template class Dylan<int>;   //显式实例化模板类声明，告诉编译器，此实例化在其他文件中定义
                                    //不需要根据模板使用生成实例化代码  
template<double> void func_template(double obj){   // 显式实例化模板函数定义
    cout<<"calling template func_template<double>(double)"<<endl;
}

template<float> void func_template(float obj){   // 显式实例化模板函数定义
    cout<<"calling template func_template<float>(float)"<<endl;
}
int main(int argc,char * argv[]){
    func_template<int>(3);
    func_template(3);
    func_template<float>(3.14);    // 链接失败，编译器不会为之生成 double 的泛型模板函数定义

    //Dylan<int> dylan(3);//OK, 使用在template1.cpp中的定义
    Dylan<float> dylan1(3.0);//error, 引发未定义错误，链接失败，编译器不会为之生成 float 的泛型模板类定义
}