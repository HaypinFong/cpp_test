#include "head2.hpp"
#include <iostream>
using namespace std;
// static string Test::stcstr("in_head2");
void func2(){
    a+=1;
    cout<<"calling func2 "<<a<<endl;
    cout<<"Test::stcstr: "<<Test::stcstr<<endl;
    funcmid();
}
void func21(){
    cout<<"calling func21 "<<endl;
};