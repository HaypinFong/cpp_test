#include "stdio.h"
#include "string.h"
void func()
{
    int c=0,k;
    for(k=1;k<3;k++)
    {
        switch(k)
        {
            default:
                c+=k;
            case(2):c++;
                break;
            case(4):
                break;
        }
        printf("%d\n",c);
    }
}
int main(int argc,char* argv[])
{
    func();
    printf("%d\n",sizeof("heihei"));    // 7
    printf("%d\n",strlen("heihei"));    // 6
}