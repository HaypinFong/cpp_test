#include "head1.hpp"
#include <iostream>
using namespace std;
int c(3);      // 声明只惟一出现在head1.cpp》.o中，在main.cpp中进行外部声明extern int c;是全局变量的正确用法
/*static*/ string Test::stcstr("in_head1");    
    /* 类内static成员必须在类外声明初始化(因为是全局的)，是类名名字空间限定的全局变量
    ，因为类(型)是全局的，类内静态成员又是类(型)属性的一部分，自然只该有一个；也可以理解为限定在全局的类名字空间内
    ，与之相较的是文件作用域内static修饰限定文件作用域，函数作用域内static限定函数栈帧作用域，类内static限定在类(型)名字空间内
    ，而类(型)是全局的，则类内static成员也是全局的。

    并且全局初始化不能再额外增加static修饰，避免了限定文件作用域的类内静态成员可以出现多个的不自洽，类型是唯一的，文件作用域有多个。
    当试图增加static文件作用域限定时：
    error: 'static' can only be specified inside the class definition
    static string Test::stcstr("in_head1");

    并且声明初始化在所有定义有Test类的.cpp|.o中只能由其中一个.cpp进行全局初始化，
    当同时在headmid.cpp中初始化string Test::stcstr("in_mid"); 
    且将headmid.cpp加到CMakeLists.txt的add_executable(main xxx)源文件中时编译报错：
    duplicate symbol 'Test::stcstr' in:
    CMakeFiles/main.dir/head1.cpp.o
    CMakeFiles/main.dir/headmid.cpp.o
    */
void func1(){
    a+=1;
    cout<<"calling func1 "<<a<<endl;
    cout<<"Test::stcstr: "<<Test::stcstr<<endl;
    funcmid();
}
string varmid("varhead1");