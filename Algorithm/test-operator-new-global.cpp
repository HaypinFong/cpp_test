#include <iostream>
using namespace std;

class Foo
{
    public:
    Foo(int val = 0):v(val){cout<<"call Foo("<<val<<")"<<endl;}
    ~Foo(){cout<<"call ~Foo()"<<endl;}
    int v;
};
void* operator new(size_t size)
{
    cout<<"calling operator new("<<size<<")"<<endl;
    if(void* mem = malloc(size))
        return mem;
    else
        throw bad_alloc();
}

void operator delete(void* mem) noexcept
{
    cout<<"calling operator delete"<<endl;
    free(mem);
}

int main(int argc,char* argv[])
{
    Foo* num = new Foo(3);  // 分配内存并构造
    delete num; // 析构，然后释放内存
    cout<<"=========="<<endl;
    Foo* pn = (Foo*)operator new(sizeof(Foo));    // 只分配内存，不构造
    cout<<"---------1--------"<<endl;
    new (pn) Foo (4);   // 原位构造
    cout<<"---------2--------"<<endl;
    pn->~Foo();         // 析构
    cout<<"---------3--------"<<endl;
    operator delete(pn);// 释放内存
    cout<<"---------4--------"<<endl;
    Foo obj(5);
    new (&obj) Foo (6); // 原位构造
    cout<<obj.v<<endl;  // 6
}