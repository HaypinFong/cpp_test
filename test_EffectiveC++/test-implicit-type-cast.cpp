/***
 * 结论：对pass-by-value传参的常规调用，会用实参拷贝构造形参，实参与形参相互无影响；
 * 当对实参调用类型转换函数(返回形参类型)，编译器会优化代码使类型转换函数返回值直接构造在调用作用域的接受对象上
*/
#include "stdio.h"
class YourInt;
void handle_yourInt(YourInt);   // 友元函数必须全局声明
class MyInt;
class YourInt
{
    private:
    int val;
    public:
    YourInt(int _val):val(_val){}
    YourInt(const YourInt& rhs):val(rhs.val)
    {
        printf("call YourInt(const YourInt& rhs)\n");
    }
    //YourInt(const MyInt& rhs);
    friend void handle_yourInt(YourInt yourInt)
    {
        printf("address of input yourInt: %lu\n",(unsigned long)&yourInt);
        return;
    }
};
class MyInt
{
    public:
    int val;
    public:
    MyInt(int _val):val(_val){}
    operator YourInt() const
    {   // MyInt到 YourInt的类型转换， 返回值类型就是operator YourInt()的YourInt
        printf("call operator YourInt(MyInt{%d})\n",val);
        YourInt rtn = YourInt(val);     // 调用YourInt(int)构造
        printf("address of type-cast's rtn: %lu\n",(unsigned long)&rtn); // 140701897039976，140701897039976
        //return &rtn;// error: no viable conversion from returned value of type 'YourInt *' to function return type 'YourInt'
        return rtn;
    }
    operator char()const
    {   // MyInt到char的类型转换，返回值类型就是operator char()的char
        return (char)val;
    }
};
//YourInt::YourInt(const MyInt& rhs):val(rhs.val)
//{
//    printf("call YourInt(const MyInt& rhs)\n");
//}
int main(int argc,char* argv[])
{
    auto func1 = []()->void{
        MyInt myInt(3);
        YourInt yourInt(myInt); // 当定义有YourInt(const MyInt&)拷贝构造函数时优先调用之，否则调用operator YourInt()类型转换
        printf("address of yourInt: %lu\n",(unsigned long)&yourInt);
        // 140701897039976，对myInt调用operator YourInt()类型转换，编译器优化后直接在调用作用域(此处yourInt)构造rtn|yourInt？
    };
    auto func2 = []()->void{
        MyInt myInt(4);
        handle_yourInt(myInt); //  error: conversion from 'MyInt' to 'YourInt' is ambiguous，当同时定义有YourInt(MyInt)拷贝构造函数与operator YourInt()类型转换时会引发歧义
        // 140701897039976，对myInt调用operator YourInt()类型转换，编译器优化后直接在调用作用域(handle_yourInt函数内)构造rtn|形参yourInt?
    };
    auto func3 = []()->void{
        YourInt yourInt(5);
        printf("address of yourInt: %lu\n",(unsigned long)&yourInt);    // 140701897039984
        handle_yourInt(yourInt);    // 实参拷贝构造形参，形参地址140701897039976
    };
    func1();
    printf("...\n");
    func2();
    printf("...\n");
    func3();
}
/***
call operator YourInt(MyInt{3})
address of type-cast's rtn: 140701897039976
address of yourInt: 140701897039976
...
call operator YourInt(MyInt{4})
address of type-cast's rtn: 140701897039976
address of input yourInt: 140701897039976
...
address of yourInt: 140701897039984
call YourInt(const YourInt& rhs)
address of input yourInt: 140701897039976
*/