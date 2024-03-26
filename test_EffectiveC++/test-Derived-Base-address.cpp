#include "stdio.h"
class Base
{
    public:
    virtual
    void vmethod()
    {
        printf("call Base::vmethod()\n");
    }
};
class Derived:public Base
{
    void vmethod()
    {
        printf("call Derived::vmethod()\n");
    }
};
int main(int argc,char* argv[])
{
    auto func1 = []()->void{
        Derived obj;
        Base* pb = &obj;
        printf("Base*    %lu \nDerived* %lu\n",(unsigned long)pb,(unsigned long)&obj);
    };
    func1();
}