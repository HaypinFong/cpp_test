// #include<cstdlib.hpp>
#include<iostream>
using namespace std;
int add(int a,int b){
    return a+b;
}
int (*func)(int x,int y);
int main(int argc,char *argv[]){
    func =add;
    cout<<(*func)(10,5);
}