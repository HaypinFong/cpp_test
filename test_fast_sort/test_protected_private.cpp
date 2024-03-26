#include<iostream>
#include<string>
using namespace std;
class A{
    protected:
    string  m_pro;
    static string m_stc_pro;
    private:
    string m_pri;
    static string m_stc_pri;
    public:
    A():m_pro("protected"),m_pri("private"){}
};
string A::m_stc_pro("static_protected");
string A::m_stc_pri("static_private");
class B:protected A{
    public:
    friend void Bfriend_func(A &objA,B &objB){
        cout<<"objA.m_pro: "<<objA.m_pro<<endl; // error: 不能通过基类对象访问(类外访问)
                    // note: can only access this member on an object of type 'B'
        cout<<"objB.m_pro: "<<objB.m_pro<<endl; // ok，通过派生类对象objB(且是在派生类B类内)访问基类protected成员
    }
    void print(A &objA){
        cout<<"m_pro: "<<m_pro<<endl;   // ok, 通过派生类对象this(派生类B类内)访问基类protected成员
        cout<<"objA.m_pro: "<<objA.m_pro<<endl; // error: 不能通过基类对象访问(类外访问)
                    // note: can only access this member on an object of type 'B'
        cout<<"m_pri: "<<m_pri<<endl;   // error: private
        cout<<"m_stc_pro: "<<m_stc_pro<<endl;   // ok，通过派生类对象this(类内)访问基类protected成员
        cout<<"m_stc_pri: "<<m_stc_pri<<endl;   // error: private
    }
    
};
class C:private A{
    void print(A &objA){
        cout<<"m_pro: "<<m_pro<<endl;   // ok, 通过派生类对象this(派生类C类内)访问
        cout<<"objA.m_pro: "<<objA.m_pro<<endl; // error: 不能通过基类对象访问(类外访问)
                    // note: can only access this member on an object of type 'C'
        cout<<"m_pri: "<<m_pri<<endl;   // error: private
        cout<<"m_stc_pro: "<<m_stc_pro<<endl;   // ok，通过派生类对象this(派生类C类内)访问基类protected成员
        cout<<"m_stc_pri: "<<m_stc_pri<<endl;   // error: private
    }
    void printB(B &objB){
        cout<<"objB.m_pro: "<<objB.m_pro<<endl; // error: 不能通过派生类对象objB(类外访问，不在派生类B类内)访问基类protected成员
    }
};
int main(int argc,char *argv[]){
    cout<<"m_stc_pro: "<<A::m_stc_pro<<endl;    // error: protected
    cout<<"m_stc_pri: "<<A::m_stc_pri<<endl;    // error: private
    A objA;
    cout<<"m_stc_pro: "<<objA.m_stc_pro<<endl;  // error: protected
    cout<<"m_stc_pri: "<<objA.m_stc_pri<<endl;  // error: private
    B objB;
    objB.m_pro; // error: 'm_pro' is a protected member of 'A'
/*
类静态成员类外访问(通过Type::m_stc或obj.m_stc访问)也受访问控制约束
，只有public的类静态成员才可以
类静态成员类内访问也受访问控制约束，只有继承基类后的public或protected的类
静态成员才可以
*/
}