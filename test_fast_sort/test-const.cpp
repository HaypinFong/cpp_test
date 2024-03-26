#include "stdio.h"
void func()
{
    const char carr[] = "hello";
    printf("%s\n",carr);
}
int main(int argc,char* argv[])
{
    func();
}