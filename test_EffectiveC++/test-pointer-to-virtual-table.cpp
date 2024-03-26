#include "stdio.h"
class Base
{
    int32_t val_base;
};
class Derived:public Base
{
    int32_t val_deri;
};
class vBase
{
    //int32_t val_base;
    virtual void method(){};
};
class vDerived:public vBase
{
    //int32_t val_deri;
};
int main(int argc,char* argv[])
{
    printf("sizeof(long): %lu\n",sizeof(long));              // 8
    printf("sizeof(long long): %lu\n",sizeof(long long));    // 8
    printf("sizeof(Base): %lu\n",sizeof(Base));        // 4，没有做 64 位对齐
    printf("sizeof(Derived): %lu\n",sizeof(Derived));  // 8=4+4
    printf("sizeof(vBase): %lu\n",sizeof(vBase));           // 8，64 位字长，基类有自己的虚表指针
    printf("sizeof(vDerived): %lu\n",sizeof(vDerived));     // 8，64 位字长，派生类也有自己的虚表指针
}