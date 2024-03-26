#include<iostream>
using namespace std;
class A{
    public:
    virtual void print(){
        cout<<"calling A::print()"<<endl;
    }
};
class B:public A{
    public:
    void print(){
        cout<<"calling B::print()"<<endl;
    }
    virtual void echo(){
        cout<<"calling B::echo()"<<endl;
    }
};
class C:public B{
    
};
int main(int argc,char *argv[]){
    C objC;
    A &robj(objC);
    robj.print();
    robj.echo();    // error: no member named 'echo' in 'A'
}