#include<iostream>
using namespace std;
class base{
};
class pub_der:public base{

};
class pub_der2:private base{
    void test_convert(){
        pub_der objpub;
        base &ref_base(objpub); // ok
        // 如果D继承B的方式是公有的或受保护的，则D的派生类的成员和友元可以使用
        // D向B的类型转换；反之，如果D继承B的方式是私有的，则不能使用
    }
};
class pro_der:protected base{
    void test_convert(){
        pro_der objpro;
        base &ref_base(objpro);
        base *pbase(&objpro);   // ok
    }
    friend void test_convert_fri(){
        pro_der objpro;
        base &ref_base(objpro);
        base *pbase(&objpro);   // ok，不论以什么方式继承基类，派生类的成员和友元
        // 都能使用派生类向基类的转换。派生类向其直接基类的类型转换对于派生类的成员和友元
        // 是永远可访问的
    }
};
class pro_der2:private pro_der{
    void test_convert(){
        pro_der objpro;
        base &ref_base(objpro); // ok
        // 如果D继承B的方式是公有的或受保护的，则D的派生类的成员和友元可以使用
        // D向B的类型转换；反之，如果D继承B的方式是私有的，则不能使用
    }
};
class pri_der:private base{
    void test_convert(){
        pri_der objpri;
        base &ref_base(objpri);
        base *pbase(&objpri);   // ok，不论以什么方式继承基类，派生类的成员和友元
        // 都能使用派生类向基类的转换。派生类向其直接基类的类型转换对于派生类的成员和友元
        // 是永远可访问的
    }
    friend void test_convert_fri2(){
        pri_der objpri;
        base &ref_base(objpri);
        base *pbase(&objpri);   // ok
    }
};
class pri_der2:private pri_der{
    void test_convert(){
        pri_der objpri;
        base &ref_base(objpri); // error: 'base' is a private member of 'base'
              // error: cannot cast 'pri_der' to its private base class 'base'
              // 如果D继承B的方式是公有的或受保护的，则D的派生类的成员和友元可以使用
              // D向B的类型转换；反之，如果D继承B的方式是私有的，则不能使用
    }
};
int main(int argc,char *argv[]){
    pub_der objpub;
    base *pbase(&objpub);

    pro_der objpro;
    base *pbase2(&objpro);  
    base &ref_base2(objpro);
    // error: cannot cast 'pro_der' to its protected base class 'base'
    // 只有当派生类public继承基类时，用户代码才能使用派生类到基类的转换

    pri_der objpri;
    base *pbase3(&objpri);
    base &ref_base3(objpri);
    // error: cannot cast 'pri_der' to its private base class 'base'
    // 只有当派生类public继承基类时，用户代码才能使用派生类到基类的转换
}