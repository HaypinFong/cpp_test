#include "stdio.h"
class MyDouble
{
    public:
    double dval;
    u_int16_t nval;
};
int main(int argc,char* argv[])
{
    auto func1 = []()->void{
        int a;
        printf("%d\n",a);           // 0.00
        MyDouble num;
        printf("%.2f\n",num.dval);   // 0.00
        printf("%d\n",num.nval);    // 0
    };
    func1();
}