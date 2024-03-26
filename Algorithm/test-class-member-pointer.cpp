#include<iostream>
#include<string>
#include<functional>
using namespace std;
class Foo
{
    public:
    int nv = 3;
    float fv = 4;
    double dv = 5;
    int method(int arg){
        cout<<"call Foo:method("<<arg<<")"<<endl;
        return arg;
    }
};
void func(int arg)
{
    cout<<"calling void func("<<arg<<")"<<endl;
}
int main(int argc,char* argv[])
{
    Foo obj,* po = &obj;

    int Foo::* pn;  // 定义成员指针
    pn = &Foo::nv;  // 绑定成员
    cout<<(bool)(typeid(obj.*pn) == typeid(int))<<endl; // 1
    cout<<po->*pn<<endl;    // 成员指针(A)被对象解引用就是解引用对象的成员A

    typedef decltype(&Foo::fv) PFLOAT_MEMBER;
    PFLOAT_MEMBER pf = &Foo::fv;                // 定义成员指针并绑定成员
    cout<<obj.*pf<<endl;

    auto pd = &Foo::dv; // 定义成员指针并绑定成员
    cout<<po->*pd<<endl;

    void (*func2)(int); // 函数指针
    func2 = func;       // 函数与函数指针之间存在自动转换规则
    func2(2);
    func2 = &func;
    func2(3);

    int (Foo::* pfunc)(int);    // 声明成员函数指针
    pfunc = &Foo::method;       // 绑定成员
    (obj.*pfunc)(6);            // 调用成员函数指针

    typedef decltype(&Foo::method) PMETHOD_MEMBER;
    PMETHOD_MEMBER pmethod;     // 声明成员函数指针
    pmethod = &Foo::method;     // 绑定成员
    (po->*pmethod)(7);          // 调用成员函数指针

    auto pmtd = &Foo::method;   // 初始化成员函数指针
    (obj.*pmtd)(8);

    string str1("ha"),str2(""),str3("hei");
    {
        vector<string*> strps{&str1,&str2,&str3};
        function<bool (const string*)> fp = &string::empty;
        bool bfund = find_if(strps.begin(),strps.end(),fp)!=strps.end();
        cout<<bfund<<endl;  // 1
    }
    vector<string> strs{str1,str2,str3};
    function<bool (const string&)> fp2 = &string::empty;
    bool bfund2 = find_if(strs.begin(),strs.end(),fp2)!=strs.end();
    cout<<bfund2<<endl; // 1

    vector<string> strs{str1,str2,str3};
    function<bool (const string&)> fp2 = &string::empty;
    bool bfund2 = find_if(strs.begin(),strs.end(),fp2)!=strs.end();
    cout<<bfund2<<endl; // 1
}