#include<iostream>
using namespace std;
class Base
{
    public:
    int pubv;   // 基类和派生类内可访问，public派生类外、Base类外可访问
    static int pubsv;
    protected:
    int prov;   // 基类和派生类内可访问，类外均不可访问
    static int prosv;
    private:
    int priv;   // 只在基类类内可访问，派生类外、Base类外均不可访问
    static int prisv;
    // 基类的public、protected、private在基类内均可以访问
};
int Base::pubsv = 1;
int Base::prosv = 2;
int Base::prisv = 3;
class Pub_Derived:public Base
{
    public:
    void func()
    {
        cout<<pubv; // public
        cout<<prov; // protected
        //cout<<priv; // 不可访问，error: 'priv' is a private member of 'Base'
        // 派生类继承后的public、protected、private基类成员在派生类内可访问

        cout<<pubsv;
        cout<<prosv;
        //cout<<prisv;  // error: 'prisv' is a private member of 'Base'
    }
};
class Pro_Derived:protected Base
{
    public:
    void func()
    {
        cout<<pubv; // protected
        cout<<prov; // protected
        //cout<<priv; //不可访问，error: 'priv' is a private member of 'Base'
        // 派生类继承后的public、protected、private基类成员在派生类内可访问

        cout<<pubsv;
        cout<<prosv;
        //cout<<prisv;    // error: 'prisv' is a private member of 'Base'
    }
};
class Pri_Derived:private Base
{
    public:
    void func()
    {
        cout<<pubv; // private
        cout<<prov; // private
        //cout<<priv; // 不可访问，error: 'priv' is a private member of 'Base'
        // 派生类继承后的public、protected、private基类成员在派生类内可访问

        cout<<pubsv;
        cout<<prosv;
        //cout<<prisv;    // error: 'prisv' is a private member of 'Base'
    }
};
int main(int argc,char* argv[])
{
    Base base_obj;
    cout<<base_obj.pubv;
    //cout<<base_obj.prov;    // error: 'prov' is a protected member of 'Base'
    //cout<<base_obj.priv;    // error: 'priv' is a private member of 'Base'

    cout<<base_obj.pubsv;
    //cout<<base_obj.prosv;   // error: 'prosv' is a protected member of 'Base'
    //cout<<base_obj.prisv;   // error: 'prisv' is a private member of 'Base'

    Pub_Derived pub_obj;
    cout<<pub_obj.pubv;
    //cout<<pub_obj.prov; // error: 'prov' is a protected member of 'Base'
    //cout<<pub_obj.priv; // error: 'priv' is a private member of 'Base'

    cout<<pub_obj.pubsv;
    //cout<<pub_obj.prosv;    // error: 'prosv' is a protected member of 'Base'
    //cout<<pub_obj.prisv;    // error: 'prisv' is a private member of 'Base'

    Pro_Derived pro_obj;
    //cout<<pro_obj.pubv; // error: 'pubv' is a protected member of 'Base'
    //cout<<pro_obj.prov; // error: 'prov' is a protected member of 'Base'
    //cout<<pro_obj.priv; // error: 'priv' is a private member of 'Base'

    //cout<<pro_obj.pubsv;    // error: 'pubsv' is a protected member of 'Base'
    //cout<<pro_obj.prosv;    // error: 'prosv' is a protected member of 'Base'
    //cout<<pro_obj.prisv;    // error: 'prisv' is a private member of 'Base'

    Pri_Derived pri_obj;
    //cout<<pri_obj.pubv; // error: 'pubv' is a private member of 'Base'
    //cout<<pri_obj.prov; // error: 'prov' is a private member of 'Base'
    //cout<<pri_obj.priv; // error: 'priv' is a private member of 'Base'

    //cout<<pri_obj.pubsv;    // error: 'pubsv' is a private member of 'Base'
    //cout<<pri_obj.prosv;    // error: 'prosv' is a private member of 'Base'
    //cout<<pri_obj.prisv;    // error: 'prisv' is a private member of 'Base'
}