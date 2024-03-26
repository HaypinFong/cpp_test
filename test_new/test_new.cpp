#include<iostream>
using namespace std;
class Type{
    public:
    Type(){
        cout<<"calling Type()"<<endl;
    }
    ~Type(){
        cout<<"calling ~Type()"<<endl;
    }

};
void func1(){
    static Type obj;
    cout<<&obj<<endl;
    obj.~Type();
    cout<<typeid(obj).name()<<endl;
    Type *pobj = new (&obj) Type;
    cout<<pobj<<endl;
}
void func2(){
    bool res;
    void *ptr(&res);
    res = ptr == nullptr ? false:(func1(),true);
    cout<<"res: "<<res<<endl;
}
int main(int argc,char *argv[]){
    func2();
    cout<<"exit"<<endl;
    return 0;
}