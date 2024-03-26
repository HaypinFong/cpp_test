#ifndef TEMPLATE1_H
#define TEMPLATE1_H
#include<iostream>
using namespace std;
/**
 * 
*/
template<class T>
void func_template(T obj);  // 模板函数声明，
// template<class T>
// void func_template(T obj){  // 泛型模板函数定义，
//     cout<<"calling func_template("<<typeid(T).name()<<")"<<endl;
// }
template<typename T>
class Dylan
{   // 模板类声明
public:
    Dylan(T t);
    T m_data;
};


#endif