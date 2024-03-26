#include"template1.h"
#include<iostream>
using namespace std;
template void func_template<int>(int);       // 显式实例化模板函数声明
template<int> void func_template(int obj){   // 显式实例化模板函数定义
    cout<<"calling template func_template<int>(int)"<<endl;
}

template<class T>
void func_template(T obj){  // 泛型模板函数定义，
    cout<<"calling func_template("<<typeid(T).name()<<")"<<endl;
}

template<typename T>
Dylan<T>::Dylan(T t)
{   // 泛型模板类构造函数定义
    cout<<"calling Dylan<int>::Dylan(int)"<<endl;
    m_data = t;
}
//template class Dylan<int>; //显式实例化模板类定义