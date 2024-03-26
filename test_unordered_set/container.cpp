#include<iostream>
#include<set>
#include<unordered_set>
#include<map>
#include<string>
#include<vector>
using namespace std;
class orderedType{
    private:
    string tag;
    int value;
    public:
    orderedType(int val,string str=""):value(val),tag(str){};
    // bool operator<(const orderedType &obj){
    //     return value<obj.value;
    // }
    int get_value() const {return value;};
    friend bool operator<(const orderedType &obj1,const orderedType &obj2){
        /* 用于有序容器set<T>时必须定义bool operator<(const T&,const T&)运算符函数
        有序容器set<T>、map<T>存储于堆时会使用比较运算符，a不大于b且b也不大于a
        等价于恒等于a==b，用于判断重复时保留先来键
        */
        return obj1.value<obj2.value;
        // if(obj1.value != obj2.value)
        //     return obj1.value<obj2.value;
        // else
        //     return obj1.tag<obj2.tag;
    }
    friend ostream & operator<<(ostream &cout,const orderedType &obj){
        // 友元函数不是成员函数，不受public,private,protect关键字约束
        cout<<"{"<<obj.value<<' '<<obj.tag<<"}";
        return cout;
    }
    // friend bool operator==(const orderedType &obj1,const orderedType &obj2){
    //     return obj1.value == obj2.value;
    // }
};
// class callable_type{
//     public:
//     bool operator()(const orderedType &obj1,const orderedType &obj2){
//         return obj1.get_value() < obj2.get_value();
//     }
// };
class unorderedType{
    private:
    string tag;
    int value;
    public:
    unorderedType(int val,string str=""):value(val),tag(str){};
    friend bool operator==(const unorderedType &obj1,const unorderedType &obj2){
        /*用于unordered_set<T>时必须定义bool operator==(const T&,const T&)运算符函数
        无序容器unordered_set<T>、unordered_map<T>存储于哈希表时会使用恒等于运算符，当桶
        内已经有恒等于的键时将不会覆盖而是保留先来键，对unordered_multiset<T>更不会覆盖
        */  // 无序容器==函数Way1
        static bool init(true);
        if(init){
            cout<<"calling friend bool operator==(a,b)"<<endl;
            init = false;
        }
        return obj1.value == obj2.value;
    }
    int get_value() const{return value;};
    friend ostream & operator<<(ostream &cout,const unorderedType &obj){
        cout<<obj.value<<' '<<obj.tag;
        return cout;
    }
};
class TypeHash{  // hash函数Way1
    public:
    size_t operator()(const unorderedType &obj){ 
        // TypeHash实例是一个可调用对象，传入一个unorderedType实例将返回该实例的哈希值
        return hash<int>()(obj.get_value());
    }
};
// 或者在std名字空间内增加hash<unorderedType>的类 
//https://wenku.baidu.com/view/19d66706de36a32d7375a417866fb84ae45cc3c0.html
namespace std{
    template<>
    class hash<unorderedType>{  // hash函数Way2，模板类，但直接指定使用unorderedType类
        // 无序容器默认在std空间查找std::hash<T>类(的可调用对象)
        public:
        size_t operator()(const unorderedType &obj){
            return hash<int>()(obj.get_value());
        }
    };
    /*
    template<>
    class equal_to<unorderedType>{  // 无序容器==函数Way2，模板类，但直接指定使用unorderedType类
        public:
        bool operator()(const unorderedType &obj1,const unorderedType &obj2){
            static bool init(true);
            if(init){
                cout<<"calling  bool std::equal_to<unorderedType>()(a,b)"<<endl;
                init = false;
            }
            return obj1.get_value() == obj2.get_value();
        }
    };
    */
}
int main(int argc,char **argv){
    /*
    set<orderedType> Set;    // 有序容器
    Set.insert({3,"a"});    // 隐式类型转换，写成{3}比3更显著
    Set.insert({1,"b"});
    Set.insert({2,"c"});
    Set.insert({2,"d"});    // 1 b 2 c 3 a，set键重复时保留先来者
    for(set<orderedType>::iterator i(Set.begin());i!=Set.end();i++)
        cout<<(*i)<<' ';
    cout<<endl;

    map<orderedType,int> Map;
    Map[{2,"c"}] = 1;
    Map[{2,"d"}] = 2;   // map键重复时保留先来者，值将被替换
    for(map<orderedType,int>::iterator i(Map.begin());i!=Map.end();i++)
        cout<<"key: "<<i->first<<" value: "<<i->second<<"  ";
    cout<<endl;

    multiset<int> Set6;
    Set6.insert(2);
    Set6.insert(2);
    for(multiset<int>::iterator i(Set6.begin());i!=Set6.end();i++)
        cout<<(*i)<<' ';
    cout<<endl;

    multiset<orderedType> Set5;
    // multiset<orderedType,callable_type> Set5;
    Set5.insert({3,"a"});
    Set5.insert({1,"b"});
    Set5.insert({2,"c"});
    Set5.insert({2,"c"});
    cout<<"Set5.size() "<<Set5.size()<<endl;    // 输出4，人为实现的键相等未发生抛弃后者
    for(set<orderedType>::iterator i(Set5.begin());i!=Set5.end();i++)
        cout<<(*i)<<' ';
    cout<<endl;
    */

    unordered_set<unorderedType,TypeHash> Set2;   // Way1，手动指定hash函数
    Set2.insert({3});
    Set2.insert({1});
    Set2.insert({2});
    for(unordered_set<unorderedType,TypeHash>::iterator i(Set2.begin());i!=Set2.end();i++)
        cout<<(*i)<<' ';
    cout<<endl;

    cout<<"tag 1"<<endl;

    unordered_set<unorderedType> Set4;   /* Way2，采用默认std::hash<unorderedType>类实例
    作可调用哈希函数，默认std::equal_to<unorderedType>类实例作==函数?*/
    Set4.insert({3,(string)"a"});   // 隐式类型转换
    Set4.insert({1,(string)"b"});
    Set4.insert({2,(string)"c"});
    Set4.insert({2,(string)"d"});   // unordered_set键重复时保留先来者
    for(unordered_set<unorderedType>::iterator i(Set4.begin());i!=Set4.end();i++)
        cout<<(*i)<<' ';    // 2 c 1 b 3 a
    cout<<endl;

    cout<<"tag 2"<<endl;

    /*
    unordered_set<unorderedType,TypeHash> Set7;
    Set7.insert({3,(string)"a"});   // 隐式类型转换
    Set7.insert({1,(string)"b"});
    Set7.insert({2,(string)"c"});
    Set7.insert({2,(string)"d"});   // unordered_set重复时保留先来者
    for(unordered_set<unorderedType>::iterator i(Set7.begin());i!=Set7.end();i++)
        cout<<(*i)<<' ';    // 2 c 1 b 3 a
    cout<<endl;

    unordered_multiset<unorderedType> Set3;
    Set3.insert({3,(string)"a"});   // 隐式类型转换
    Set3.insert({1,(string)"b"});
    Set3.insert({2,(string)"c"});
    Set3.insert({2,(string)"d"});   // 更不会覆盖
    for(unordered_multiset<unorderedType>::iterator i(Set3.begin());i!=Set3.end();i++)
        cout<<(*i)<<' ';    // 2 c 2 d 3 a 1 b
    cout<<endl;
    */
    

    //
}