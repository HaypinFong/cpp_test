#include<iostream>
#include<type_traits>
using namespace std;
void func1(){
    using nonref = int;
    using lref = typename std::add_lvalue_reference<nonref>::type;
    using rref = typename std::add_rvalue_reference<nonref>::type;
    using voidref = std::add_lvalue_reference_t<void>;

    std::cout << std::boolalpha;
    std::cout << std::is_lvalue_reference<nonref>::value << '\n';
    std::cout << std::is_lvalue_reference<lref>::value << '\n';
    std::cout << std::is_rvalue_reference<rref>::value << '\n';
    std::cout << std::is_reference_v<voidref> << '\n';

    typedef int T;
    typedef std::add_lvalue_reference<T&>::type T_lref_add_lref;
    cout<< ( typeid(T&)==typeid(T_lref_add_lref) )<<endl;   // T&再加lref保持为T&
    typedef std::add_lvalue_reference<T&&>::type T_rref_add_lref;
    cout<< ( typeid(T&)==typeid(T_rref_add_lref) )<<endl;   // T&&加lref为T&
    typedef std::add_rvalue_reference<T&>::type T_lref_add_rref;
    cout<< ( typeid(T&)==typeid(T_lref_add_rref) )<<endl;   // T&加rref保持为T&
    typedef std::add_rvalue_reference<T&&>::type T_rref_add_rref;
    cout<< ( typeid(T&&)==typeid(T_rref_add_rref) )<<endl;  // T&&加rref保持为T&&
}
int main(int argc,char * argv[]){
    func1();
}