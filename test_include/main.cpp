#include "head1.hpp"
#include "head2.hpp"
#include <iostream>
using namespace std;
extern int c;
int d;
// int d;   // redefinition
/*[ 25%] Building CXX object CMakeFiles/main.dir/main.cpp.o
/Users/haypin/catkin_ws/cpp_test/test_#include/main.cpp:6:5: error: redefinition of 'd'
int d;
    ^
/Users/haypin/catkin_ws/cpp_test/test_#include/head2.hpp:3:5: note: previous definition is here
int d;
    ^
1 error generated.
*/
// void func21();
extern std::string varmid;
int main(int argc,char* argv[]){
    func1();    // 1
    func2();    // 1 只当用到head2.hpp声明head2.cpp定义的名字时才需要add_executable()链接head2.cpp(.o)
    funcmid();  // 0
    cout<<"main "<<a<<endl; // 0
    cout<<"main "<<c<<endl; // 3
    /*如果不对headmid.hpp中的a进行static文件作用域修饰，
    既使在main.cpp中不引用名字a，编译时也会报错重复的符号'_a'，也就是编译链接时链接到的所有.o的名字不能重复
    duplicate symbol '_a' in:
        CMakeFiles/main.dir/main.cpp.o
        CMakeFiles/main.dir/head1.cpp.o     // main.cpp.o中声明的名字_a链接时找到在head1.cpp.o的全局名字_a
    duplicate symbol '_a' in:
        CMakeFiles/main.dir/main.cpp.o
        CMakeFiles/main.dir/head2.cpp.o     // main.cpp.o中声明的名字_a链接时找到在head2.cpp.o的全局名字_a
    ld: 2 duplicate symbols for architecture x86_64
    另外，extern引用声明其他.cpp中的全局变量时必须将那个.cpp加到CMakeLists.txt中的add_executable(main xxx)源文件中

    当对headmid.hpp中的a进行static文件作用域修饰后(被包含在.cpp中限定在.cpp文件作用域，最终到.o文件作用域)
    ，head1.cpp.o、head2.cpp.o、main.cpp.o各自文件作用域内
    都有各自的名字a，是其本地的，相互独立的，head1.cpp.o、head2.cpp.o、main.cpp.o文件作用域的a分别是1、1、0
    全局作用域>文件作用域
    */
    cout<<varmid<<endl;
}