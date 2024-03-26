#include"template1.h"
#include<iostream>
using namespace std;

template<typename T>
Dylan<T>::Dylan(T t)
{   // 泛型模板类构造函数定义
    cout<<"calling Dylan<T>::Dylan(T)"<<endl;
    m_data = t;
}