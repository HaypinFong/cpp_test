#include "stdio.h"
union
{
    bool boolValue;
    int intValue;
    float floatValue;
    void* ptr;
    unsigned char mem[sizeof(float) * 4];
}data alignas(8);

int main(int argc,char* argv[])
{
    data.intValue = 3;
    printf("%x\n",data.ptr);
}