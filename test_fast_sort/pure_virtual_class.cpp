#include<iostream>
using namespace std;
class A{
    public:
    virtual void echo()=0   // 纯虚函数
    {   // error: expected ';' at end of declaration list
        // error: initializer on function does not look like a pure-specifier
        cout<<"calling echo()=0"<<endl;
    }
    ;
};
// void A::echo(){
//     cout<<"calling echo()=0"<<endl;
// };
int main(int argc,char *argv[]){
    // A objA;
}