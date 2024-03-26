#include<iostream>
#include<string>
using namespace std;
class Type{
    public:
    Type(string var):name(var){};
    void method2(){
        func(this);
        func2(this);
    }
    friend void func(Type *pobj){
        cout<<"func() get "<<pobj->name<<endl;   // 友元使用方式1: 类内定义+"友元关系"声明
    }
    friend void func2(Type *pobj);               // 友元使用方式2 part2: 类内"友元关系"声明
    void method(){
        func(this);
        func2(this);
    }
    void method3();
    private:
    string name;
};
void Type::method3(){
    func2(this);
}
void func2(Type *pobj){                          // 友元使用方式2 part1: 类外定义
    cout<<"func2() get "<<pobj->name<<endl;
}
int main(int argc,char *argv[]){
    Type obj("haha");
    obj.method();
}