#include "stdio.h"
//template<typename T> void func(T obj);
template<typename T> void func(T obj)
{
    printf("call func(T)\n");
}
template<int> void func(int obj)
{
    printf("call func(int)\n");
}

//template<float> void func(float obj)
//{
//    printf("call func(float)\n");
//}
int main(int argc,char* argv[])
{
    func((int)3);
    func<int>((int)3);
    func((float)3.14);
}