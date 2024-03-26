#include<iostream>
#include<string>
#include<vector>
using namespace std;
class A{
    public:
    string nameA;
    // A()=delete;
    // A():nameA("default"){}
};
class Base{
    public:
    string name;
    const A objA;       // 如果不类内初始化或构造时初始化，将在构造函数体前调用其类型的默认构造函数
    string & rstr=name; // 必须类内初始化或构造时初始化
    Base():name("")
        ,rstr(name)
        {
        cout<<"calling Base()"<<endl;
    }
    Base(const Base& obj):name(obj.name)
        ,rstr(name)
        {
        cout<<"calling Base(const Base&)"<<endl;
    }
    Base(Base &&obj):name(obj.name)
        ,rstr(name)
        {
        cout<<"calling Base(Base &&)"<<endl;
    }
    Base(string val_):name(val_)
        ,rstr(name)
        {
        cout<<"calling Base(string)"<<endl;
    }
    Base(const char* str):name(str)
        ,rstr(name)
        {
        cout<<"calling Base(const char*)"<<endl;
    }
    Base &operator=(string val){
        name = val;
        cout<<"calling Base &operator=(string)"<<endl;
        return *this;
    }
    friend void handle_Base(Base obj){
        cout<<"calling void handle_Base(Base obj)"<<endl;
    }
    friend void handle_rBase(const Base /*&*/&robj=Base("")){
        // 这里友元函数的常左值引用形参的默认实参不能真的缺省，必须提供实参？
        cout<<"robj.name "<<robj.name<<endl;
    }
    void print(){
        cout<<"objA.nameA "<<objA.nameA<<endl;
    }
    ~Base(){
        cout<<"calling ~Base()  "<<name<<endl;
    }
};
void handle_Base(Base);
// void handle_rBase(const Base &);
void handle_string(const string &rstr=(string)"temp"){
    cout<<"rstr: "<<rstr<<endl;
}
void handle_rBaseg(const Base &robj=Base("gogo")){
    // 这里常左值引用形参的默认实参可以缺省调用
    cout<<"robj.name "<<robj.name<<endl;
}
int main(int argc,char *argv[]){
    Base obj=(string)"haha";    // 调用构造函数Base(string)
    Base obj4="haha";   // 调用构造函数Base(const char*)
    cout<<"break 0"<<endl;
    obj = (string)"heihei"; // 调用赋值运算符函数
    cout<<"break 1"<<endl;
    Base obj2(obj);     // 调用拷贝构造函数Base(const Base&)
    Base obj3=obj;      // 调用拷贝构造函数Base(const Base&)
    cout<<"break 2"<<endl;
    Base arr[]={"haha",(string)"hiehei",obj};   // 依次调用对应构造函数
    vector<Base> varr(2);   // 调用2次默认构造函数
    vector<Base> varr2(2,"haha");   // 调用1次Base(const char*)，然后调用2次拷贝构造
    varr2.push_back("heihei");  // 调用1次Base(const char*)，然后扩容，调用3次拷贝构造

    cout<<"break 3"<<endl;
    handle_Base((string)"ohoh");    // 调用Base(string)构造函数，实参初始化构造形参
    handle_Base("hengheng");    // 调用Base(const char*)构造函数，实参初始化形参

    cout<<"break 4"<<endl;
    handle_Base(Base("aha"));   
    // 编译器优化？先调用Base(const char*)直接初始化形参，然后执行handle_Base(Base obj)函数体，然后析构形参
    cout<<"break 5"<<endl;
    // handle_rBase();  // 这里友元函数的常引用形参的默认形参不能真的缺省，必须提供实参！error: use of undeclared identifier 'handle_rBase'
    handle_rBaseg();
    handle_rBase(Base("papa")); // 匿名左值构造、析构
    cout<<"break 6"<<endl;
    handle_string();
    handle_string("enen");
    obj3.print();
}