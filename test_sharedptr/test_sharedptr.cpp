#include<iostream>
#include<string>
#include<vector>
#include"unistd.h"
using namespace std;
class MyClass{
    private:
        string field;
    public:
        static int n_construct;
        static int n_destruct;
        MyClass(string var):field(var){
            n_construct++;
        };
        ~MyClass(){
            cout<<"~MyClass("<<field<<")"<<endl;
            n_destruct++;
        }
        string getfield(){
            return field;
        }
};
void destruct_MyClass(MyClass *pobj){
    cout<<"self define destruct MyClass("<<pobj->getfield()<<")"<<endl;
    delete pobj;    // ~MyClass(xxxx)
}
int MyClass::n_construct(0);
int MyClass::n_destruct(0);
void func(std::shared_ptr<MyClass> pobj){
    cout<<"dandling MyClass("<<pobj->getfield()<<")"<<endl;
    return;
}
int main(int argc,char **argv){
    MyClass obj=MyClass("lolo");
    cout<<"MyClass::n_construct "<<MyClass::n_construct<<endl;

    vector<MyClass> arr;
    cout<<"arr.capacity() "<<arr.capacity()<<" &arr "<<&arr<<endl;
                                    // 0 vector容器初始capacity()=0
    // arr.resize(3);
    arr.push_back(MyClass("haha"));         // 1、完成push_back()函数传参后析构局部实参
    cout<<"arr.capacity() "<<arr.capacity()<<" &arr "<<&arr<<endl;
                                    // 1
    arr.push_back(MyClass("heihei"));       // 2、容器扩容，析构～MyClass("haha")，并直接内存层面拷贝MyClass("haha")到新空间，但arr虚存地址不变
    cout<<"arr.capacity() "<<arr.capacity()<<" &arr "<<&arr<<endl;
                                    // 2
    arr.push_back(MyClass("ouou"));         // 3、扩容，逆压栈顺序析构～MyClass("heihei")与～MyClass("haha")
    cout<<"arr.capacity() "<<arr.capacity()<<" &arr "<<&arr<<endl;
                                    // 4
    arr.push_back(MyClass("lala"));         // 4、不需扩容
    cout<<"arr.capacity() "<<arr.capacity()<<" &arr "<<&arr<<endl;
                                    // 4
    // 5、容器扩容时首先直接内存拷贝到新空间(不必重新构造)，然后析构掉旧空间的实例
    cout<<"construct total "<<MyClass::n_construct<<" instances"<<endl;
    cout<<"destruct total "<<MyClass::n_destruct<<" instances"<<endl;
    cout<<"sleep 1s"<<endl;
    sleep(1);
    for(MyClass &iobj:arr){
        cout<<"arr[0].getfield() "<<arr[0].getfield()<<" &arr "<<&arr<<endl;

        // func( (std::shared_ptr<MyClass>)&iobj );
        /**
         * @brief 
         * 临时实参(动态指针)指向栈变量，传参后临时实参+形参 引用计数等于2，临时实参动态指针首先析构，
         * 形参然后析构导致引用计数归零，直接析构arr[0]即～MyClass("haha")
         */

        std::shared_ptr<MyClass> pobj(&iobj,destruct_MyClass);
        func(pobj);
        cout<<"sleep 1s"<<endl;
        sleep(1);
        /**
         * @brief 
         * 局部实参(动态指针)指向栈变量，传参后局部实参+形参 引用计数等于2，形参动态指针首先析构，
         * 局部实参pobj然后析构导致引用计数归零，直接析构arr[0]即～MyClass("haha")
         * 破坏arr
         */
    }
}
/**
 * @brief 
 * 输出：
 * sleep 1s
    arr[0].getfield() haha &arr 0x7ff7bfefeff8
    dandling MyClass(haha)              // 析构形参动态指针
    sleep 1s
    self define destruct MyClass(haha)  // 局部实参动态指针pobj析构，然后引用计数归零再析构栈上实例MyClass(haha)，释放栈空间？
    ~MyClass(haha)

    arr[0].getfield() haha &arr 0x7ff7bfefeff8  // 虽然释放了栈空间，但arr[0]还是能将这段内存数据解释出MyClass("haha")实例
    dandling MyClass(heihei)
    sleep 1s
    self define destruct MyClass(heihei)
    ~MyClass(heihei)
                                        // 但为什么在遍历到arr[2]也就是第三个元素时才报错？
    main(82642,0x100098600) malloc: *** error for object 0x600002608018: pointer being freed was not allocated
    main(82642,0x100098600) malloc: *** set a breakpoint in malloc_error_break to debug
 * 总结：
    不要用一个原始指针初始化多个shared_ptr
    不要在函数实参中创建shared_ptr。
    通过shared_from_this()返回this指针。
    要避免循环引用
 */