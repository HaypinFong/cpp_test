#define MY_MACRO 2
#include "head.h"
int globalNum = 3;
void func1()
{
    printf("MY_MACRO in head1.cpp: %d\n",MY_MACRO); // 替换 2
    printf("globalNum: %d\n",globalNum);
}