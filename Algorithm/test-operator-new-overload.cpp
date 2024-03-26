#include<iostream>
using namespace std;

class Foo
{
    public:
        int _id;
    public:
        Foo():_id(0){cout<<"default ctor.this="<<this<<" id="<<_id<<endl;}
        Foo(int i):_id(i){cout<<"ctor.this="<<this<<" id="<<_id<<endl;}
        ~Foo() {cout<<"dtor.this="<<this<<" id="<<_id<<endl;}
        static void* operator new(size_t size);
        static void operator delete(void* pdead,size_t size);
        static void* operator new[](size_t size);
        static void operator delete[](void* pdead,size_t size);
};

void* Foo::operator new(size_t size)
{
    Foo* p = (Foo *)malloc(size);
    cout<<"Call Foo::operator new("<<size<<")"<<endl;
    return p;
}

void Foo::operator delete(void *pdead,size_t size)
{
    cout<<"Call Foo::operator delete"<<endl;
    free(pdead);
}
void* Foo::operator new[](size_t size)
{
    Foo* p  = (Foo*)malloc(size);
    cout<<"Call Foo::operator new[]("<<size<<")"<<endl;
    return p;
}

void Foo::operator delete[](void *pdead, size_t size)
{
    cout<<"Call Foo::operator delete[]"<<endl;
    free(pdead);
}
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
int main()
{
    cout<<sizeof(Foo)<<endl;// 4
    Foo* pf = new Foo(7);   // 调用类重载的operator new(size_t)
    Foo* pf1 = new Foo[3];  // 调用类重载的operator new[](size_t)，20个字节？
    delete pf;              // 调用类重载operator delete
    delete[] pf1;           // 调用类重载的operatore delete[]
    using namespace std;
    cout<<"============"<<endl;
    Foo* pf2 = ::new Foo(5);// 调用全局重载的operator new(size_t)
    Foo* pf3 = ::new Foo[2];// 调用全局重载的operator new[](size_t)，16个字节？
    ::delete pf2;           // 调用全局重载的operator delete
    ::delete[] pf3;         // 调用全局重载的operator delete[]
    cout<<"&&&&&&&&&&&"<<endl;
    int num(8);
    const int * pn = &num;  // 常量指针，指向常量
    //*pn = 7;    // read-only variable is not assignable，指针认为其指向的是常量，不能通过指针解引用修改指向的常量，尽管实际指向的是变量
    int * const pnc = &num; // &num的类型是int *，可以赋值给int * const pnc，指针常量，指针是个常量
    *pnc = 7;
    cout<<num<<endl;    // 7
    //pnc = &num; // cannot assign to variable 'pnc' with const-qualified type 'int *const'，指针本身是个常量，初始化后不能改指向，但能通过解引用修改指向的变量
    
}