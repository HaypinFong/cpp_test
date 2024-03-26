#include<iostream>
using namespace std;

class Foo
{
    public:
        int _id;
        long _data;
        string _str;
    public:
        Foo():_id(0){cout<<"default construct this="<<this<<" id="<<_id<<endl;}
        Foo(int i):_id(i){cout<<"construct this="<<this<<" id="<<_id<<endl;}
        ~Foo() {cout<<"destruct this="<<this<<" id="<<_id<<endl;}
        void print(){cout<<"id: "<<_id<<endl;}
        static void* operator new(size_t size);     
        /* 类静态函数，在执行Foo *p=new Foo(Args... args)时将首先
        调用Foo::new(size)申请内存，然后调用对应构造函数 */
        static void operator delete(void* phead,size_t size);
        static void* operator new[](size_t size);
        static void operator delete[](void* phead,size_t size);
        // void method(){
        //     Foo *p;
        //     new (p) Foo(42);    // 类内调用operator new？
        //     p->print();
        //     operator delete(reinterpret_cast<void*>(p),sizeof(Foo));    // 类内调用operator delete

        // };
};
void* Foo::operator new(size_t size)
{
    Foo* p = (Foo *)malloc(size);
    cout<<"调用了Foo::operator new("<<size<<")"<<endl;
    return p;
}

void Foo::operator delete(void *phead,size_t size)
{
    cout<<"调用了Foo::operator delete("<<size<<")"<<endl;
    free(phead);
}
void* Foo::operator new[](size_t size)
{
    Foo* p  = (Foo*)malloc(size);
    cout<<"调用了Foo::operator new[]("<<size<<")"<<endl;
    return p;
}

void Foo::operator delete[](void *phead, size_t size)
{
    cout<<"调用了Foo::operator delete[]("<<size<<")"<<endl;
    free(phead);
}
void test_overload_operator_new(){
    cout<<"breakpoint -1"<<endl;
    cout<<sizeof(Foo)<<endl;    // 40
    Foo* pf = new Foo(3);   // 先调用重载的Foo::operator new(40)，然后调用自定义构造
    Foo* pf1 = new Foo[4];  // 先调用重载的Foo::operator new[](40*4+8=168)，然后调用4次默认构造
    Foo* pf4 = new Foo[1];  // 先调用重载的Foo::operator new[](40+8=48)，然后调用3次默认构造
    /* 猜想：通过在operator new[](size_t size)函数中打印size可知动态堆数组总是在 
    元素大小*元素数目 的基础上额外申请8个字节，可能用于存储堆数组长度信息？
    所以operator delete[](void *phead, size_t size) 实际上调用std::free(phead)就能释放
    整个堆数组连续内存？ */
    // pf->method();
    delete pf;      // 先调用1次析构，然后调用重载的Foo::operator delete(40)
    // cout<<"breakpoint 0"<<endl;
    // operator delete(pf);    // 显式调用运算符函数
    delete[] pf1;   // 先调用4次析构，然后调用重载的Foo::operator delete[](168)
    delete[] pf4;   // 先调用1次析构，然后调用重载的Foo::operator delete[](48)

    // Foo *p;
    // new (p) Foo ();
    // operator delete(reinterpret_cast<void*>(p));
    

    Foo* pf2 = ::new Foo(3);    // 先调用std::new，然后调用自定义构造
    Foo* pf3 = ::new Foo[4];    // 先调用std::new[]，然后调用4次默认构造
    ::delete pf2;   // 先调用1次析构，然后调用std::delete
    ::delete[] pf3; // 先调用4次析构，然后调用std::delete[]
}

void test_operator_new(){
    // https://blog.csdn.net/y2zaijian/article/details/106720267
    /* operator new的源码表明：
    void *__CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc) {
        // try to allocate size bytes
        void *p;
        while ((p = malloc(size)) == 0)
            if (_callnewh(size) == 0){
                // report no memory
                // 如果申请内存失败了，这里会抛出bad_alloc 类型异常
                static const std::bad_alloc nomem;
                _RAISE(nomem);
            }
        return (p);
    }
    operator new函数实际通过malloc申请空间，当malloc申请成功则
    直接返回；申请空间失败则尝试执行空间不足应对措施，如果用户设置
    了的话，并继续申请，否则抛异常。相当于operator new函数封装
    了malloc和抛异常
    */
    // 调用malloc尝试申请2G空间，失败，返回nullptr
    printf("0x%x\n",1<<30);
    printf("0b%d\n",0x7fffffff);
    char *p3 = (char*)std::malloc(2*(1<<30));
    // cout<<"p3: "<<p3<<endl;
    // 调用operator new申请2G空间，抛出异常
    char *p4 = (char*)operator new(2*(1<<30));
    cout<<"p4: "<<p4<<endl;
}

int main()
{
    test_overload_operator_new();
    // test_operator_new();
}