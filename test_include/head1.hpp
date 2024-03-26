/* 链接时多次定义的错误，因为头文件中包含了函数定义，被不同.cpp(.0)所包含但这些.o
在链接时会进行全局查找，找到多个定义。所以不该在头文件中写入定义。
*/
#include "headmid.hpp"
// int c(3);
// int b;  // 全局作用域名字的链接只能在一个.cpp》.o声明而在另一个.cpp中extern int b外部声明
//，如果出现在.hpp中形成在两个.o的全局作用域局面，则链接报名字重复，区别于同一文件作用域的重复定义redefinition。
//，名字只关注其在.cpp》.o中出现的结果在链接时是否会全局作用域名字冲突
void func1();