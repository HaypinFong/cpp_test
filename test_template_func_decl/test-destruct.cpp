#include "stdio.h"
/**
 * 构造时在构造函数初始化列表调用成员的指定或默认析构函数，然后执行构造函数函数体；
 * 析构时首先执行析构函数函数体，然后调用成员的默认析构函数
*/
class subType
{
    public:
    ~subType()
    {
        printf("call subType::~subType()\n");
    }
};
class myType
{
    private:
    subType val;
    public:
    ~myType()
    {
        printf("call myType::~myType()\n");
    }
};
int main(int argc,char* argv[])
{
    myType* po = new myType();
    delete po;
}
/**
call myType::~myType()
call subType::~subType()
*/