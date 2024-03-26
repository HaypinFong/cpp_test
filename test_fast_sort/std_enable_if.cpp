#include<iostream>
#include<string>
using namespace std;
void test_enable_if(){
    typename std::enable_if<true,double>::type doubleT;
    cout<<typeid(doubleT).name()<<endl;
    // cout<<typeid(std::enable_if_t).name()<<endl;

    typename std::enable_if<true,float>::type floatT;
    cout<<typeid(floatT).name()<<endl;
    // cout<<typeid(std::enable_if_t).name()<<endl;
}
int main(int argc,char * argv[]){
    test_enable_if();
}