#ifndef HEADMID_H
#define HEADMID_H   /**/
/* 避免一个.o文件作用域内菱形包含导致重定义，重定义是一个.o文件作用域内
，多个定义是不同.o文件作用域构成的全局作用域内重定义， 以及名字重复*/
#include<string>
static int a;   /**
 * @brief 
 * ，文件作用域全局变量零初始化。通过使用static修饰，实际上每个文件都有一个独立的数据拷贝(如果初始化
    了的话，文件作用域和全局作用域变量零初始化)，如果文件想使用该数据与另外一个文件通话，这样做就不行了
    ，因为每个文件只能看见他自己的拷贝，然而如果数据是const不可变的，这就不是问题了，每个文件的值都一样。
    使用头文件的好处是不必惦记在一个文件(.cpp)中进行定义声明，在另一个文件中进行extern引用声明(即只
    在一个.cpp中定义并初始化，其他.cpp|.o进行extern引用声明)，缺点在于复制了数据(每个.o都存在一个
    文件作用域限定的同名变量)，如果常量很大的话，这 就是个问题了。
 */
void funcmid();
class Test{
    public:
    static std::string stcstr;
    /*
    template<typename T>
    class XSingleton
    {
    public:

        static T& instance(void)    // 限定类内作用域(类所有实例共有，类似类名字空间)，类又是全局的，则static名字是全局的
        {
            static T singleton;     // 全局的函数XSingleton<T>::instance()的静态局部变量，相当于全局的
            // ，一个T类型一个singleton，不用手动在全局定义T1 global_insT1; T2 global_insT2; 
            return singleton;
        }

    private:
        XSingleton(void);
    };
    */
};
#endif