#include "stdio.h"
#include<typeinfo>
class SubType
{
    public:
    void func();
};
template<typename T>
class MyType
{
    public:
    MyType(T _v):val(_v)
    {
        printf("call MyType(%s)\n",typeid(T).name());
    }
    void func();    // 只声明不定义，只要不使用该函数就不会报编译错，因为类成员函数只当被使用时才实例化
    private:
    T val;
};
int main(int argc,char* argv[])
{
    MyType<int> objA(3);        // i
    MyType<float> objB(3.14);   // f
    SubType obj;
}