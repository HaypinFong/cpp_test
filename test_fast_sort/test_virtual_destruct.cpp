#include<iostream>
#include<string>
using namespace std;
class Base{
    public:
    string name;
    string *pname;
    Base():name(""),pname(&name){
        cout<<"calling Base()"<<endl;
    }
    Base(const Base& robj){
        cout<<"calling Base(const Base&)"<<endl;
    }
    // Base(const Base&)=delete;
    virtual void print(){
        cout<<"calling Base::print()"<<endl;
    }
    
    /*virtual*/ ~Base(){    // 虚析构函数总是按继承树全部逆序调用，不仅用于多态，也用于一般对象析构
        cout<<"calling ~Base()"<<endl;
    }
    // Base &operator=(Base &&rvobj){  // 移动运算符
    //     name = std::move(rvobj.name);
    //     cout<<"calling Base &operator=(Base &&)"<<endl;
    //     return *this;
    // }
};
class Derive:public Base{
    public:
    Derive(){
        cout<<"calling Derive()"<<endl;
    }
    // Derive(const Derive& robj){  // 自定义拷贝构造需要手动调用基类拷贝构造
    //     cout<<"calling Derive(const Derive&)"<<endl;
    // }
    Derive(const Derive&)=default;  // 默认拷贝构造将递推调用基类拷贝构造
    // 如果删除基类拷贝构造则报错 error: call to implicitly-deleted copy constructor of 'Derive'
    void print(){
        cout<<"calling Derive::print()"<<endl;
    }
    
    ~Derive(){  // 虚析构函数总是按继承树全部逆序调用，不仅用于多态，也用于一般对象析构
        cout<<"calling ~Derive()"<<endl;
        Base::~Base();
    }
};
int main(int argc,char *argv[]){
    Base *pbase(new Derive());
    pbase->print();
    delete pbase;   // 如果基类析构函数不声明为虚函数，则
    cout<<"break 0"<<endl;
    Derive obj,obj2(obj);

    const char *pstr("haha");
    // *(pstr+2)='b';  error: read-only variable is not assignable

    Base obj3;
    string *p_name(&(obj3.name));
    // obj3.p_name = "heihei";
    // obj3->p_name;
    // obj3.*p_name;// error: right hand operand to .* has non-pointer-to-member type 'std::string *'
    // *obj3.p_name;   // error: no member named 'p_name' in 'Base'
    *obj3.pname = "heihei";
    cout<<obj3.name<<endl;
}