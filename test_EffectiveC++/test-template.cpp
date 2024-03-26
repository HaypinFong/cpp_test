#include "stdio.h"
#include "string.h"
class SubType
{
    public:
    void method(){
        printf("call SubType::method()\n");
    };
};
int main(int argc,char* argv[])
{
    printf("%lu\n",sizeof(unsigned));   // 4
    printf("%lu\n",sizeof(int));        // 4
    printf("%lu\n",sizeof("hi"));       // 3
    printf("%lu\n",strlen("hi"));       // 2

    SubType obj;
    void (SubType::* pfunc)();
    pfunc = &SubType::method;
    (obj.*pfunc)();
}