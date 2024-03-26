#include "stdio.h"
class MyInt
{
    public:
    int val;
    MyInt(int _val):val(_val)
    {
        printf("call MyInt(%d)\n",val);
    }
};
class YourInt
{
    public:
    int val;
    YourInt(int _val):val(_val){};
    operator MyInt()
    {   // 类型转换
        printf("call operator MyInt()\n");
        return MyInt(val);
    }
};
int main(int argc,char* argv[])
{
    auto func1 = []()->void{
        YourInt obj(3);
        MyInt obj2 = (MyInt)obj;
        printf("--------\n");
        MyInt obj3 = MyInt(obj);
    };
    func1();
}
/**
call operator MyInt()
call MyInt(3)
--------
call operator MyInt()
call MyInt(3)
*/