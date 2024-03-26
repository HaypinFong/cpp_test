#include<iostream>
#include<functional>
#include<string>
using namespace std;
class Data
{
    public:
        string name;
    public:
        Data(string val):name(val){}
        Data(const Data &obj):name(obj.name){   // 拷贝构造
            cout<<"calling copy constructor Data(const Data&)"<<endl;
        }
        string & operator=(const Data &obj){    // 赋值运算符重载
            name=obj.name;
            cout<<"calling operator="<<endl;
            return name;
        }
        string & operator=(const string &val){  // 赋值运算符重载
            name=val;
            return name;
        }
        
};
ostream & operator<<(ostream &out,const Data &obj){
    out<<"Data obj.name: "<<obj.name;
    return out;
}
class Son
{
    private:
        Data data;
    public:
        Son(string val):data(val){}
        Son(const Son& obj):data(obj.data){
            cout<<"calling copy constructor Son(const Son&)"<<endl;
        }
        void func1(){
            /*function<void()>*//*auto close_func=*/[this]()->void{   // capture this by reference
                // data="func1";
                data="func1";
            }();
            // close_func();
            cout<<data<<endl;
        }
        void func2(){
            /*function<void()>*//*auto close_func=*/[*this]()mutable ->void{  // capture this by value
                // data="func2";
                data="func2";
            }();    // 拷贝构造this实例，lambda表达式执行时捕获，而不是定义时捕获
            // close_func();
            cout<<data<<endl;
        }
        void func3(){
            [=]()->void{    // capture this by reference, default
                data="func3";
            }();
            cout<<data<<endl;
        }
};
class Func
{
    public:
        void operator()(int i,int &j){
            cout<<i+j<<endl;
        }
};
int main(int argc, char **argv)
{
    Son son("luoluo");
    son.func1();
    son.func2();    // 拷贝构造this实例
    son.func3();
    int i(1),j(2);
    function<void()> enclose_func=[i,&j]()->void{cout<<i+j<<endl;}; // 值捕获在lambda表达式定义时捕获
    auto func_obj = [i,&j]()->void{cout<<i+j<<endl;};
    cout<<typeid(func_obj).name()<<endl;
    cout<<(typeid(func_obj) == typeid(enclose_func) )<<endl;    
    /* 0，lambda匿名类匿名可调用实例毕竟不是function<>函数对象
    ，但lambda匿名类匿名可调用实例可以赋值给function<>函数对象*/
    void (*func_obj2)();
    // func_obj2 = enclose_func;   // error: assigning to 'void (*)()' from incompatible type 'function<void ()>'
    // func_obj2 = func_obj;       // error: assigning to 'void (*)()' from incompatible type '(lambda
    function<void()> enclose_func2 = bind(func_obj);    // lambda匿名可调用对象既可以直接赋值function函数对象(上)，也可以绑定
    // func_obj2 = bind(func_obj);    // error: assigning to 'void (*)()' from incompatible type '__bind<(lambda
    // func_obj2 = bind(&func_obj);
    i=3;
    j=4;
    enclose_func(); // 5    引用捕获在lambda表达式运行时捕获
    
    /**
     * @brief 
     * 输出：
     *  func1
        calling copy constructor
        func1
        func3
     *  这里捕获this指捕获this实例的引用或this实例的拷贝，类内访问实例属性总是通过this指针访问的。
        但lambda表达式捕获this实例后是访问拷贝或者引用的this实例的属性，而不是像类内总是通过this
        指针访问实例属性。
     */
}