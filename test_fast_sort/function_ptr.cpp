#include<iostream>
using namespace std;
void funcg() {
  cout<<"calling global funcg()"<<endl;
}
class Type{
    public:
    void (*func)();         // 函数(成员)声明
    void (* const cpfun)(); // 常的函数(成员)声明，初始化后不可覆盖
    //const void (* pcfun)(); // 指向常的函数指针(成员)声明，如何给函数指针成员加 指向是const 修饰？
    typedef decltype(func) func_type;

    public:
    void func1() const {
        cout<<"calling func1()"<<endl;
    }
    func_type func2(){
        auto func=[]()->void{
            cout<<"calling lambda []()->void"<<endl;
        };
        cout<<"lambda []()->void address: "<<(size_t)&func<<endl;
        return func;
    }
    void operator()(){
        cout<<"calling operator()()"<<endl;
    }
    void func3(){
        cout<<"calling func3()"<<endl;
    }
    public:
    Type()
        :cpfun(funcg)
        //,func(func1)
        // error: reference to non-static member function must be called;
        //,func(&this->func1) 
        // error: cannot create a non-constant pointer to member function
        //,cpfun( &(this->func1) )
        // error: cannot create a non-constant pointer to member function
    {
        //cpfun = nullptr;
        // error: cannot assign to non-static data member 'cpfun' with 
        // const-qualified type 'void (*const)()'，已经初始化过，不可覆盖
        cout<<"calling Type()"<<endl;
    } 
};
void funcg_();
int main(int argc, char *argv[]) {
    cout<<funcg<<endl;   // warning: address of function 'funcg' will always evaluate to 'true'
    printf("0x%x  0x%x\n",funcg,&funcg);    // 函数对象的“值”与取函数的地址是相同的
    void (*f)() = funcg;
    printf("%d\n",typeid(f)==typeid(funcg));    // 0
    printf("%d\n",typeid(*f)==typeid(funcg));   // 1，函数指针与函数毕竟是不同类型，但函数指针可以被函数赋值，就像指针可被C数组赋值一样，函数指针还可以像函数一样调用
    void (*f2)() = &funcg;
    printf("%d\n",typeid(f2)==typeid(f));       // 1，函数指针
    //funcg_ = funcg;   // error: non-object type 'void ()' is not assignable，函数funcg_不是可赋值的对象类型
    cout<<f<<' '<<(*f)<<endl;   // 1 1
    printf("0x%x  0x%x\n",f,*f);            // 函数指针存储的值与函数指针指向的函数对象的值是相同的
    f();

    Type obj;
    //    void (*f2)() = obj.func1;
    /*error: reference to non-static member function must be called; 
    did you mean to call it with no arguments?
    error: cannot initialize a variable of type 'void (*)()' with 
    an rvalue of type 'void'
    */
    void (*f3)() = obj.func2();
    cout<<"lambda []()->void address: "<<(size_t)f3<<endl;
    f3();

    //    void (*f4)() = obj;
    /*error: no viable conversion from 'Type' to 'void (*)()'*/

    void (Type::* cpfun3)(); // 指向普通成员函数的指针cpfun3
    // cpfun3 = &(Type::func3);
    // cpfun3 = &(obj.func3);
    // (obj.*cpfun3)();    // “绑定”实例调用该成员函数

    cout<<"sizeof(int): "<<sizeof(int)<<" sizeof(double): "<<sizeof(double)<<endl;

    
    printf("%p\n", f);
}