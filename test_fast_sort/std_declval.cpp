#include <utility>
#include <iostream>
using namespace std;
struct Default { int foo() const { return 1; } };
 
struct NonDefault
{
    NonDefault() = delete;
    // NonDefault(){ cout<<"calling NonDefault()"<<endl;}
    NonDefault(float);
    int foo() const { return 1; }
};
 
int main()
{
    decltype(Default().foo()) n1 = 1;                   // type of n1 is int
    // decltype(NonDefault().foo()) n2 = n1;               // error: no default constructor
    /*decltype(expression)虽然不实际执行expression表达式，但要去表达式所需的
    函数的要有，没有不行：error: call to deleted constructor of 'NonDefault'
    */
    decltype(std::declval<NonDefault>().foo()) n2 = n1; // type of n2 is int
    /*declval<T>()不需要T提供默认构造函数，*/
    std::cout << "n1 = " << n1 << '\n'
                << "n2 = " << n2 << '\n';
}