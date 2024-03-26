#include "stdio.h"
class Window
{
    //protected:
    public:
    Window(){}
    Window(Window& obj_derive)
    {
        printf("call Window(Window&)\n");
    }
    virtual void onResize()
    {
        printf("call Window::onResize()\n");
    }
};
class SpecialWindow:public Window
{
    public:
    SpecialWindow():Window(){}
    virtual void onResize()
    {
        static_cast<Window>(*this).onResize();  // 类型转换将拷贝构造出一个匿名临时Window对象，在其身上调用onResize()
        printf("call SpecialWindow::onResize()\n");
    }
};
int main(int argc,char* argv[])
{
    SpecialWindow obj_derive;
    obj_derive.onResize();
    printf("-----");
    auto obj_base = static_cast<Window>(obj_derive);   // 类型转换将拷贝构造出一个匿名临时Window对象(或拷贝构造接收左值)
    printf("-----");
    auto obj_base2 = (Window)obj_derive;               // 类型转换将拷贝构造出一个匿名临时Window对象(或拷贝构造接收左值)
}
/**
call Window(Window&)
call Window::onResize()
call SpecialWindow::onResize()
-----call Window(Window&)
-----call Window(Window&)
*/