#include<iostream>
#include<memory>
#include<string>
using namespace std;
class Type{
    public:
    string val;
    Type(string value):val(value){};
    string getval(){
        return val;
    }
    ~Type(){
        cout<<"calling ~Type("<<val<<")"<<endl;
    }
};
void copyvalue_func(std::shared_ptr<Type> pobj){
    cout<<"{"<<pobj->getval()<<"},use_count(): "<<pobj.use_count()<<endl;  // 2
    pobj.reset(new Type{(string)"cat"});    // 只对形参pobj重置指向，实参引用计数为1
    // 形参指针pobj引用计数置零，析构匿名实例"cat"
}
void func(){
    std::shared_ptr<Type> p1(std::make_shared<Type>((string)"heihei")); // 匿名实参是否增加引用计数？
    copyvalue_func(p1);
    cout<<"{"<<p1->getval()<<"},use_count(): "<<p1.use_count()<<endl;
    // 指针p1引用计数置零，析构匿名实例"heihei"
}
class Derive{
    public:
    std::shared_ptr<Type> ptr;  // 该智能指针属于类实例，类实例生命周期结束才是智能指针生命周期结束
    Derive(string val):ptr(std::make_shared<Type>(val)){};  //  RAII
    ~Derive(){
        cout<<"{"<<ptr->getval()<<"},use_count(): "<<ptr.use_count()<<endl;
    }
};
int main(int argc,char *argv[]){
    func();
    Derive obj("haha");
}