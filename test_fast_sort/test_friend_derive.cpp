#include<iostream>
#include<string>
using namespace std;
class Base;
class Derive;
class Base{
    public:
    Base():m_pub_base("pub_base"),m_pro_base("pro_base"),m_pri_base("pri_base"){};
    string m_pub_base;
    friend void print_base(Base &obj,Derive &obj2);
    protected:
    string m_pro_base;
    private:
    string m_pri_base;
};
class Derive:public Base{
    public:
    Derive():m_pub_derive("pub_derive"),m_pro_derive("pro_derive"),m_pri_derive("pri_derive"){};
    string m_pub_derive;
    friend void print_derive(Derive &obj2);
    protected:
    string m_pro_derive;
    private:
    string m_pri_derive;
};
void print_base(Base &obj,Derive &obj2){
    cout<<obj.m_pub_base<<endl;
    cout<<obj.m_pro_base<<endl;
    cout<<obj.m_pri_base<<endl;

    cout<<obj2.m_pub_derive<<endl;
    // cout<<obj2.m_pro_derive<<endl;  // error: 'm_pro_derive' is a protected member of 'Derive'
    // cout<<obj2.m_pri_derive<<endl;  // error: 'm_pri_derive' is a private member of 'Derive'
                                    // 基类的友元在访问派生类成员时不具有特殊性
}
void print_derive(Derive &obj2){
    cout<<obj2.m_pub_base<<endl;    // 派生类类内能访问基类的public和protected成员
    cout<<obj2.m_pro_base<<endl;
    // cout<<obj2.m_pri_base<<endl;    // error: 'm_pri_base' is a private member of 'Base'
                                    // 派生类的友元(派生类类内)不能随意访问基类的成员
    cout<<obj2.m_pub_derive<<endl;
    cout<<obj2.m_pro_derive<<endl;
    cout<<obj2.m_pri_derive<<endl;
}
int main(int argc,char *argv[]){
    Base obj_base;
    Derive obj_derive;
    print_base(obj_base,obj_derive);
    cout<<"."<<endl;
    print_base(obj_derive,obj_derive);
    cout<<".."<<endl;
    print_derive(obj_derive);
}