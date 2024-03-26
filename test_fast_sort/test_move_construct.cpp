#include<iostream>
#include<string>
using namespace std;
class A{
    public:
    A(string var):val(var){
        cout<<"calling A(string)"<<endl;
    }
    A(const A& objA):val(objA.val){
        cout<<"calling copy constructor"<<endl;
    }
    A(A&& objA):val(std::forward(objA.val)){
        cout<<"calling move constrctor"<<endl;
    }
    public:
    string val;
};
int main(int argc,char *argv[]){
    A objA("haha");
    A objA2(objA);
    A objA3(std::move(objA));
    A objA4(A("heihei"));
}