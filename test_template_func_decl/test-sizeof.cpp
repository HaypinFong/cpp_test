#include "stdio.h"
struct S {
   char a;
   short b;
   double c;
   double d;
   char e;
   double f;
};
int main(int argc,char* argv[])
{
    auto func2 = []()->void{
        struct MyType
        {
            short s;
            char arr[2];
            int32_t num;
            //char arr2[6];
        };
        struct MyType2
        {
            int32_t num;
            char arr2[13];
        };
        struct x_
        {
        char a;     // 1 byte
        int b;      // 4 bytes
        short c;    // 2 bytes
        char d;     // 1 byte
        };
        printf("%lu\n",sizeof(MyType));     // 8=2+1+1+4
        printf("%lu\n",sizeof(x_));         // 12=1+3+4+2+1+1
        printf("%lu\n",alignof(MyType));    // 4
        printf("%lu\n",sizeof(MyType2));    // 20=4+13+3
    };
    func2();
    printf("----\n");
    printf("%lu\n",sizeof(int));        // 4
    printf("%lu\n",sizeof(long));       // 32位机器 4 字节，64 位机器8字节
    printf("%lu\n",sizeof(float));      // 4
    printf("%lu\n",sizeof(double));     // 32位机器 4 字节，64 位机器8字节
    printf("%lu\n",sizeof(long long));  // 32位机器 4 字节，64 位机器8字节
    printf("%lu\n",sizeof(long double));// 16
    printf("%lu\n",sizeof(void*));      // 8

    auto func0 = []()->void
    {
        struct alignas(4) MyType3
        {
            int a;
            char b;
            char d[10];  // 对齐4字节，并不会对每个成员单独按 4 字节对齐，紧前成员不足 4 字节时可以由紧后成员连续递补
        };
        struct alignas(4) MyType4
        {
            int a;
            short b;
            char d[10];  // 对齐4字节，并不会对每个成员单独按 4 字节对齐，紧前成员不足 4 字节时可以由紧后成员连续递补
        };
        printf("%lu\n",sizeof(MyType3));    // 16
        printf("%lu\n",sizeof(MyType4));    // 16
    };
    printf("####\n");
    func0();
    auto func1 = []()->void{
        struct alignas(32) Str1
        {
            int a,b,c,d,e;
        };
        printf("%lu\n",sizeof(Str1));   // 32
    };
    printf("-----\n");
    func1();
}