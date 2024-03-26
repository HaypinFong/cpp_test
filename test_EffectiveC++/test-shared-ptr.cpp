#include "stdio.h"
#include <string>
#include <memory>
using namespace std;
class MyString
{
    private:
    string str;
    public:
    MyString(const string& _str):str(_str){}
    ~MyString()
    {
        printf("call ~MyString()\n");
        str.clear();
    }
};
void releaseMyString(MyString* str)
{
    printf("call releaseMyString(MyString*)\n");
    delete str; // warning: deleting pointer to incomplete type 'MyString' may cause undefined behavior [-Wdelete-incomplete]
}
int main(int argc,char* argv[])
{
    auto func1 = []()->void{
        shared_ptr<MyString> ptr(new MyString((string)"heihei"),releaseMyString); 
        // 自定义删除器函数，当对象引用计数归零时调用删除器，删除器处理资源释放｜mutex解锁
    };
    func1();
    printf("sizeof(void*): %lu\n",sizeof(void*));                           // 8
    printf("sizeof(shared_ptr<T>): %lu\n",sizeof(shared_ptr<MyString>));    // 16
}
/**
call releaseMyString(MyString*)
call ~MyString()
*/