#include<iostream>
using namespace std;
struct Type{
    int field1;
    float field2;
};
void func(){
    Type obj;
    cout<<obj.field1<<endl;
    cout<<obj.field2<<endl;
}
int main(int argc,char **argv){
    func();
}