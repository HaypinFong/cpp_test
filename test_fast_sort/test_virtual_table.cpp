#include "stdio.h"
class  Type
{

};
class Base
{
    public:
    virtual ~Base() // 如果不声明为 public 会报错error: base class 'Base' has private destructor
    {               // 即类外析构实例 等价于类外调用析构函数，析构函数必须声明为 public
        printf("calling ~Base()\n");
    }
    private:
    Base(){};
};
class Derived:public Base
{
    virtual ~Derived()
    {
        printf("calling ~Derived()\n");
    }
};
int main(int argc,char* argv[])
{
    printf("%d\n",sizeof(Type));    // 至少1个字节对齐
    printf("%d\n",sizeof(Base));    // 8个字节，因为本机是 64 位，虚表指针
    printf("%d\n",sizeof(void*));   // 8个字节
    printf("%d\n",sizeof(Derived)); // 8个字节
    //Base obj;   //  error: calling a private constructor of class 'Base'
                // 类外构造实例 等价于类外调用构造函数，构造函数必须声明为 public，
                // 如果不让类外构造实例当然可以将构造函数声明为private或 protected(但派生类的构造函数可调用基类protected构造函数，从而构造基类部分)
}