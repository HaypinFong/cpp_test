#include<iostream>
#include<string>
using namespace std;
class Type{
    private:
    string value;
    public:
    Type():value("default"){
        cout<<"calling Type() default"<<endl;
    };
    Type(string val):value(val){
        cout<<"calling Type(string)"<<endl;
    };
    ~Type(){
        cout<<"calling ~Type()"<<endl;
    }
    public:
    string get_value(){
        return value;
    }
};
void func(){
    size_t len(3);
    // std::unique_ptr<Type[]> p(new Type[len](len-1,{"heihei"}));
    std::unique_ptr<Type[]> p(new Type[len]()); // unique_ptr<T[]> p(new T[n]())不接受初始化参数，只能调用默认构造
    for(size_t i(0);i<len;i++)
        cout<<(p[i].get_value())<<' ';
    cout<<endl;
}
int main(int argc,char *argv[]){
    func();
}