#include<iostream>
using namespace std;
class Foo
{
    private:
    Foo(){cout<<"call Foo();";}
};
int main(int argc,char* argv[])
{
    //Foo obj;    //  error: calling a private constructor of class 'Foo'
}