#include <iostream>
using namespace std;
class Foo
{
    private:
    Foo(const Foo&){};
    Foo& operator=(const Foo&){};

    int v;
    public:
    Foo():v(0){cout<<"calling Foo()"<<endl;};
};
int main(int argc,char * argv[])
{
    Foo obj;
    Foo obj2(obj); // calling a private constructor of class 'Foo'，构造函数的调用也属类外调用
}