#include "stdio.h"
class MyInt
{
    private:
    int val;
    public:
    MyInt(int v):val(v){}
    MyInt& operator=(int v)
    {
        printf("call MyInt& operator=() for {%d}\n",val);
        val = v;
        return *this;
    }
    MyInt& operator=(const MyInt& rhs)
    {   // 拷贝赋值运算符
        printf("call MyInt& operator=(const MyInt& rhs) for {%d}\n",val);
        val = rhs.val;
        return *this;
    }
};
int main(int argc,char* argv[])
{
    MyInt a(3),b(4);
    a = b = 5;  // 表达式从右到左执行，先调用operator=(int)，再调用operator=(const MyInt&)
    /**
     * call MyInt& operator=() for {4}
       call MyInt& operator=(const MyInt& rhs) for {3}
    */
}