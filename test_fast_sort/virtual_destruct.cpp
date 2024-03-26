#include<iostream>
using namespace std;
class Base {
 public:
  Base(){
    buffer_ = new char[10];
  }
  virtual void func(){
    cout<<"in Base::func()"<<endl;
  }
  virtual ~Base() {
    std::cout << "in Base::~Base" << std::endl;
    delete []buffer_;
  }
private:
  char *buffer_;

};

class Derived : public Base {
 public:
  Derived(){}
  void func(){
    cout<<"in Derived::func()"<<endl;
  }
  ~Derived() {
    std::cout << "in Derived::~Derived" << std::endl;
  }
  static void stc_func(){
    cout<<"calling static Derived::stc_func()"<<endl;
  }
};

int main() {
  Base *base = new Derived;
  base->func(); // 虚的一般函数调用派生类重写的
  delete base;  // 虚的析构函数总是按照继承关系按派生类->基类的顺序被调用

  cout<<"breakpoint 0"<<endl;
  Derived *derive = new Derived;
  derive->func();   // 虚的一般函数调用派生类重写的

  derive->stc_func(); // 类内静态函数也有成员函数的身份，可被实例调用，也可Derived::stc_func()调用
  Derived::stc_func();

  delete derive;    // 虚的析构函数总是按照继承关系按派生类->基类的顺序被调用
  return 0;
}