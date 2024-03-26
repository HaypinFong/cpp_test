#include "stdio.h"
#include <iomanip>
class MyInt
{
    public:
    int val;
    MyInt(int _val = 0):val(_val){
        printf("call MyInt(%d)\n",val);
    }
    MyInt(const MyInt& obj):val(obj.val){
        // 拷贝构造，输入对象仍有效
        printf("call MyInt(const MyInt&{%d})\n",obj.val);
    }
    MyInt(const MyInt&& obj):val(std::move(obj.val)){
        // 移动构造，输入对象将失效
        printf("call MyInt(const MyInt&&{%d})\n",obj.val);
    }
    MyInt& operator=(const MyInt&obj){
        // 拷贝赋值运算符函数
        val = obj.val;
        printf("call MyInt& operator=(const MyInt&{%d})",obj.val);
        return *this;
    }
};
MyInt operator*(const MyInt& lhs,const MyInt& rhs)
{
    return lhs.val*rhs.val; // implicit constructor
}
int main(int argc,char* argv[])
{
    auto func1 = []()->void{
        MyInt a(3),b(4);
        a*b;    // 将调用一次默认构造，构造临时匿名变量
    };
    auto func2 = []()->void{
        MyInt a(3),b(4);
        MyInt c = a*b;  // 同样调用一次默认构造，直接使用operator*返回的 int构造对象c，而不会再构造临时匿名变量来拷贝构造 c
    };
    auto func3 = []()->void{
        MyInt a(3),b(a); // 调用拷贝构造，call MyInt(const MyInt&{3})
    };
    auto func4 = []()->void{
        MyInt a(3),b(std::move(a)); // 调用移动构造，call MyInt(const MyInt&&{3})
    };
    auto func5 = []()->void{
        MyInt a(3),b(4);
        a*b = a;    // 对a*b返回的临时匿名对象调用拷贝赋值运算符
    };
    func5();
    //3*4=5;  // error: expression is not assignable，说明内置int的operator*(l,r)返回的临时匿名int对象没有定义operator=(const int&)方法
}