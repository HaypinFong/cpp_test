#include<iostream>
using namespace std;
enum CAR{SERIS,TESLA,AUDI};
//enum CAR2{TESLA};   // redefinition of enumerator 'TESLA'，因为枚举类型CAR的枚举成员TESLA是全局的(不限定作用域)，全局作用域名字TESLA重复
enum class MOTO{CF,QJ};
enum class MOTO2{CF,QJ};    // ok,枚举类型MOTO2的枚举成员是限定作用域MOTO::、MOTO2::的，名字MOTO::CF与MOTO2::CF不冲突
void func()
{
    CAR car = TESLA;
    CAR car2 = CAR::AUDI;
    //MOTO moto = CF; // error: use of undeclared identifier 'CF'，枚举成员MOTO::CF是限定作用域的，全局不存在CF名字，只存在MOTO::CF
    MOTO moto = MOTO::CF;
    MOTO2 moto2 = MOTO2::CF;
    int num = TESLA;    // 不限定作用域的枚举成员隐式地转成 int
    //int num2 = MOTO::CF;// error: cannot initialize a variable of type 'int' with an rvalue of type 'MOTO'
                        // 限定作用域的枚举成员不能隐式转成 int
};
int main(int argc,char* argv[])
{
    //CAR car = SERIS;
    func();
    signed char num = 128;
    printf("%d\n",num); // -128
}