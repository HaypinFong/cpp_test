#include "stdio.h"
class Type
{
    public:
    void method(){
        printf("method name:%s;\n",__func__);
    };
    static void func(){
        printf("func name:%s;\n",__func__);
    };
};
void func(){
    printf("func name:%s;\n",__func__);
};
int main(int argc,char* argv[])
{
    Type obj;
    obj.method();
    Type::func();
    func();
}