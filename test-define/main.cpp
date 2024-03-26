#include "head.h"
int main(int argc,char* argv[])
{
    printf("MY_MACRO in main.cpp: %d\n",MY_MACRO);
    func1();
    func2();
    func1();
    func2();
    /**
     * #pragma once是为了避免同一个.cpp的多个#include都包含了同一个.h使重定义，
     * 而不是避免全局作用域只有一份.h，
     * 应该说在某个cpp里面修改宏的定义，编译时也只在那个.cpp里替换修改后的宏的定义，
     * 不会影响其他.cpp里宏的替换，要实现所有.cpp的宏都被修改，只能改.h里宏的定义
    */
    printf("globalNum: %d\n",globalNum);
}