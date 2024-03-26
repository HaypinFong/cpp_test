#include "stdio.h"
#include <typeinfo>
template<typename T>    // 基本类型
class SubType
{
    public:
    T val;
    SubType(const T& _val):val(_val)
    {
        printf("call SubType(%s) %d\n",typeid(T).name(),typeid(T) == typeid(int));
    }
};
template<typename T>    // 自定义类型
class MyType
{
    public:
    T obj;
    MyType(const T& _obj):obj(_obj)
    {
        printf("call MyType(%s) %d\n",typeid(T).name(),typeid(T) == typeid(SubType<int>));
    }
};
template<typename T>
MyType<SubType<T> > func(T _val)    // 偏特化模板类
{
    MyType<SubType<T> > rtn = MyType<SubType<T> >(SubType<T>(_val));
    return rtn;
}
namespace std
{
    //template<typename T>
    //void swap<MyType<SubType<T>> (SubType<T>& a,SubType<T>& b)  // 偏特化模板函数，编译不过
    //{
    //    using namespace std;
    //    swap(a,b);
    //}
};
int main(int argc,char* argv[])
{
    MyType<SubType<int> > myInt = func((int)3);
    printf("%d\n",myInt.obj.val);
    SubType obj(4); // 模板类型自动推测
    MyType obj2(5); // 模板类型自动推测
}
/**
call SubType(i) 1
call MyType(7SubTypeIiE) 1
3
*/