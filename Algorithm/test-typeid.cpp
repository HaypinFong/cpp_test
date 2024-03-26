#include<iostream>
using namespace std;
class Base
{
    public:
    virtual ~Base(){};
};
class Derived:public Base
{
    public:

};
int main(int argc,char* argv[])
{
    const int* const ccpn = nullptr;
    typedef const int * CPN;
    cout<<(bool)(typeid(ccpn) == typeid(const int *))<<endl;        // 1
    cout<<(bool)(typeid(ccpn) == typeid(const int * const))<<endl;  // 1
    cout<<(bool)(typeid(ccpn) == typeid(int *))<<endl;              // 0
    cout<<typeid(ccpn).name()<<endl;
    cout<<"----------1-------------"<<endl;
    cout<<(bool)(typeid(int []) == typeid(int *))<<endl;    // 0
    Base* bp = new Derived();
    cout<<(bool)(typeid(*bp) == typeid(Base))<<endl;    // 0
    cout<<(bool)(typeid(*bp) == typeid(Derived))<<endl; // 1
    
}