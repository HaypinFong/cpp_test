#include<iostream>
using namespace std;
class Son{
    public:
    virtual void func(){
        cout<<"calling Son::func()"<<endl;
    }
};
class Father:public Son{
    public:
    void func(){
        cout<<"calling Father::func()"<<endl;
    }
};
int main(int argc,char * argv[]){
    Father *pfather=(Father*)new Son();
    pfather->func();
    Son *pson=new Father();
    pson->func();
}