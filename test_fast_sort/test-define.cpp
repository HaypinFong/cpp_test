#include "stdio.h"
class Foo
{
    public:
    static int gNum;
};
#define Foo::gNum CLASS_MEMBER  // 宏不能用来定义类变量
int CLASS_MEMBER = 3;
int main(int argc,char* argv[])
{
    Foo obj;
    //printf("%d\n",Foo::gNum);
}