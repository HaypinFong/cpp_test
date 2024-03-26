#include <cstdlib>
#include <new>
#include <limits>
#include <iostream>
#include <vector>
using namespace std;
class Mtype{
    public:
    int value;
    Mtype():value(-1){                          // 默认构造函数
        cout<<"calling default Mtype()"<<endl;
    }
    Mtype(int val):value(val){                  // 自定义构造函数
        cout<<"calling Mtype(int)"<<endl;
    }
    Mtype(const Mtype &obj):value(obj.value){   // 拷贝构造函数
        cout<<"calling Mtype(const Mtype &obj)"<<endl;
    }
    Mtype & operator=(const Mtype &obj){        // 拷贝赋值运算符函数
        value = obj.value;
        cout<<"calling Mtype &operator=(const Mtype &obj)"<<endl;
        return *this;
    }
    Mtype(Mtype &&obj):value(obj.value){        // 移动构造函数
        cout<<"calling Mtype(Mtype &&obj)"<<endl;
    }
    Mtype & operator=(Mtype &&obj){             // 移动赋值运算符函数
        value = obj.value;
        cout<<"calling Mtype &operator=(Mtype &&obj)"<<endl;
        return *this;
    }
    ~Mtype(){
        cout<<"calling ~Mtype()"<<"with value="<<value<<endl;
    }
    void print(){
        cout<<"value: "<<value<<endl;
    }
    // void * operator new(int val){
    //     Mtype *p = (Mtype*)std::malloc(sizeof(Mtype));
    //     cout<<"-调用了Mtype::operator new("<<val<<")"<<endl;
    //     return p;
    // }
    void * operator new(size_t size){
        Mtype *p = (Mtype*)std::malloc(size);
        cout<<"调用了Mtype::operator new("<<size<<")"<<endl;
        return p;
    }
    void operator delete(void *phead,size_t size){
        cout<<"调用了Mtype::operator delete("<<size<<")"<<endl;
        std::free(phead);
    }
    void * operator new[](size_t size){
        /*动态堆数组总是在 元素大小*元素数目 的基础上额外申请8个字节，
        可能用于存储堆数组长度信息？
        所以operator delete[](void *phead, size_t size) 实际上
        调用std::free(phead)就能释放整个堆数组连续内存？ 
        */
        Mtype *p = (Mtype*)std::malloc(size);
        cout<<"调用了Mtype::operator new[]("<<size<<")"<<endl;
        return p;
    }
    void operator delete[](void *phead,size_t size){
        cout<<"调用了Mtype::delete[]("<<size<<")"<<endl;
        std::free(phead);
    }
};

template<class T>
struct Mallocator   // 自定义用于容器的内存分配器类
{
    typedef T value_type;
 
    Mallocator () = default;
    template <class U>
    constexpr Mallocator (const Mallocator <U>&) noexcept { // 拷贝构造
        U obju;
        cout<<"typeid(obju).name() "<<typeid(obju).name()<<endl;
        T objt;
        cout<<"typeid(objt).name() "<<typeid(objt).name()<<endl;

        cout<<"calling Mallocator (const Mallocator <U>&) {}"<<endl;
    }
 
    [[nodiscard]] T* allocate(std::size_t n)    // 输入n是T类元素个数
    {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
            throw std::bad_array_new_length();
        if (auto p = static_cast<T*>(std::malloc(n * sizeof(T))))
        {
            report(p, n);
            return p;
        }
 
        throw std::bad_alloc();
    }
 
    void deallocate(T* p, std::size_t n) noexcept
    {   // std::size_t n在std::free(p)时无用，释放内存只要传入头指针即可
        report(p, n, 0);
        std::free(p);
    }
 
private:
    void report(T* p, std::size_t n, bool alloc = true) const
    {
        std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
                  << " bytes at " << std::hex << std::showbase
                  << reinterpret_cast<void*>(p) << std::dec << '\n';
    }
};

template<class T, class U>
bool operator==(const Mallocator <T>&, const Mallocator <U>&) { 
    cout<<"calling operator==()"<<endl;
    return true; 
}

template<class T, class U>
bool operator!=(const Mallocator <T>&, const Mallocator <U>&) { 
    cout<<"calling operator!=()"<<endl;
    return false; 
}
void check_Mallocator(){
    cout<<"breakpoint -1"<<endl;
    Mallocator<int> obj;    // 调用默认构造函数
    Mallocator<size_t> obj2(obj);   // 调用拷贝构造函数
    cout<<"sizeof(Mtype) "<<sizeof(Mtype)<<endl;    // 4，只一个int
    std::vector<Mtype, Mallocator<Mtype> > v(2);    // 首先申请8/4=2初始容量的内存，然后调用两次默认构造生成元素
    v.push_back(42);    /* 首先按照字面的逻辑顺序调用一次自定义构造生成一个匿名实例，然后2倍扩容申请16/4=4容量的内存，
    然后对push_back()的右值调用移动构造，然后对旧容器的2个元素调用拷贝构造，然后对旧容器的8/4=2个元素调用析构函数，
    最后释放旧容器的8/4=2个元素的内存，最后对匿名实例调用析构函数*/
    cout<<"breakpoint 1"<<endl;

    Mtype *p=new Mtype(35); // 首先调用重载的Mtype::operator new(4)，然后调用自定义构造
    delete p;   // 首先调用析构函数，然后调用重载的Mtype::operator delete(4)
    Mtype *parr=new Mtype[3];// 首先调用重载的Mtype::operator new[](20)，3*4+8，然后调用3次默认构造函数
    delete []parr;  // 首先调用3次析构函数，然后调用重载的Mtyp::operator delete[](20)

    Mtype *p2 = (Mtype*)std::malloc(sizeof(Mtype)); // 手动申请堆内存
    // new (p2)Mtype(99);  // 显式调用构造函数
    p2->print();
    delete p2;  // 释放堆内存

    // 退出作用域，首先按vector从后到前顺序调用对应元素的析构函数，最后释放16/4=4容量的新容器的内存
}
void check_constructor(){
    Mtype obj;                    // 默认构造
    Mtype obj2(obj);              // 拷贝构造，calling Mtype(const Mtype &obj)
    obj2 = obj;                   // 拷贝赋值，calling Mtype &operator=(const Mtype &obj)
    Mtype obj3(std::move(obj));   // 移动构造，calling Mtype(Mtype &&obj)
    obj3 = std::move(obj2);       // 移动赋值，calling Mtype &operator=(Mtype &&obj)
}
int main()
{
    check_Mallocator();
    // check_constructor();
}