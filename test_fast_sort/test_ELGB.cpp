#include<iostream>
#include<vector>
#include<string>
using namespace std;
void func(){
    float var;
    cout<<"var: "<<var<<endl;// 局部非静态变量，mac默认初始化成0
    int len(3);
    float arr[len];//={3.14};
    for(int i(0);i<len;i++) cout<<arr[i]<<' ';
    cout<<endl; // 不填充数组元素，随机
}
int len(5);
static vector<double> arrg(len);  // 全局作用域vector，初始化为零
void func2(){
    float arr[5]={1,2};   // 剩余部分值初始化为零
    for(int i(0);i<5;i++) cout<<arr[i]<<' ';
    cout<<endl;
    double var_local;           // 局部对象，随机
    static double var_global;   // 静态全局对象，初始化0
    cout<<"var_local: "<<var_local<<" var_global: "<<var_global<<endl;
    vector<double> arr2(len,3.14);   // len个3.14
    for(int i(0);i<len;i++) cout<<arr2[i]<<' ';
    cout<<endl;
    for(int i(0);i<5;i++) cout<<arrg[i]<<' ';
    cout<<endl;
}
class Type{
    public:
    string str;
    Type():str(""){                     // 默认构造
        cout<<"calling Type()"<<endl;
    }
    Type(string strv):str(strv){        // 自定义构造
        cout<<"calling Type(string)"<<endl;
    }
    Type(const Type &obj):str(obj.str){ // 拷贝构造
        cout<<"calling Type(const Type &)"<<endl;
    }
    Type& operator=(string strv){
        str = strv;
        cout<<"calling =(string)"<<endl;
        return *this;
    }
    Type& operator=(const Type &obj){
        str = obj.str;
        cout<<"calling =(const Type&)"<<endl;
        return *this;
    }
    ~Type(){
        cout<<"calling ~Type()"<<endl;
    }
};
int main(int argc,char **argv){
    vector<Type> arr(2);    
    /* 共调用1次默认构造、2次拷贝构造、3次析构，
    默认构造1个实例后拷贝构造两个实例到vector，最后3个实例全部析构
    1、拷贝构造的确是构造，是从无到有，错误认知是”默认构造两个实例后拷贝到这两个实例“
    */
    cout<<"&arr[0]: "<<&arr[0]<<endl;   // 输出扩容前的数组起始地址
    cout<<"0"<<endl;
    Type *pobj = new Type((string)"a");
    Type *pobj2 = new Type((string)"b");
    Type &obj(*pobj);
    Type &obj2(*pobj2);
    cout<<"1"<<endl;
    arr.insert(arr.end(),obj);   // 等价于arr.push(obj)
    // arr.push_back(obj);       // 等价于arr.insert(arr.end(),obj)
    /* 扩容调用两次拷贝构造“移动”已有的两个元素，insert()时又调用一次拷贝构造
    insert()结束后析构旧地址的两个元素
    */
    cout<<"&arr[0]: "<<&arr[0]<<endl;   // 输出扩容后的数组起始地址
    cout<<"size: "<<arr.size()<<endl;   // 3
    arr.emplace(arr.end(),(string)"b"); 
    /*emplace()根据传入的参数列表进行函数匹配，调用了自定义构造函数
    ，不像insert()或push()调用拷贝构造*/
    cout<<"size: "<<arr.size()<<endl;   // 4
    arr.emplace(arr.end(),obj); // 将调用拷贝构造函数
    cout<<"2"<<endl;
    obj = "c";          // 调用自定义的operator=(string strv)运算符函数
    cout<<"3"<<endl;
    obj = obj2;         // 调用operator=(const Type &obj)运算符函数
    delete pobj;        // 析构堆上对象
    cout<<"4"<<endl;
}