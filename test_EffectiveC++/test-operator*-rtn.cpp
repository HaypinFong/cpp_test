/**
 * 结论：对自定义类型对象表达式objA*objB = objC;
 * 定义friend MyInt operator*(const MyInt& lhs,const MyInt& rhs)
 * 编译器优化后：operator*()函数内直接在调用接收处构造(此处的匿名临时对象)，
 * 然后为该匿名临时对象调用operator=()方法
 * 避免了operator*()函数内返回值对象的构造和析构成本；
*/
#include "stdio.h"
class MyInt;
MyInt operator*(const MyInt& lhs,const MyInt& rhs);
class MyInt
{
    private:
    int val;
    public:
    MyInt(int _val):val(_val)
    {
        printf("call MyInt(%d)\n",val);
    }
    MyInt(MyInt& rhs):val(rhs.val)
    {
        printf("call MyInt(MyInt{%d})\n",val);
    }
    friend MyInt operator*(const MyInt& lhs,const MyInt& rhs)
    {
        MyInt rtn = MyInt(lhs.val*rhs.val);
        printf("call MyInt operator(const MyInt&,const MyInt&) for local MyInt 0x%lu\n",&rtn);  // 0x140702046834832
        return rtn;
    }
    MyInt& operator=(const MyInt& rhs)
    {   // 令赋值运算符返回bool 而不是MyInt&
        printf("call bool operator=(const MyInt&) for MyInt 0x%lu\n",this); // 0x140702046834832
        val = rhs.val;
        return *this;
    }
};
int main(int argc,char* argv[])
{
    MyInt objA(3),objB(4),objC(5);
    printf("...\n");
    objA*objB = objC;   // 对objA*objB返回的MyInt&临时匿名对象调用赋值运算符
    // |__编译器优化后：operator*()函数内直接在调用接收处(此处的匿名临时对象)构造，然后为该匿名临时对象调用operator=()方法

    //if(objA*objB = objC)
    //{   // warning: using the result of an assignment as a condition without parentheses [-Wparentheses]
    //    printf("passed\n");
    //}
    //3*4=5;  // error: expression is not assignable
}