#include<iostream>
#include"Type.h"
using namespace std;
int main(int argc,char *argv[]){
    Type obj;
    obj.print();

    float x(3.14);
    cout<<(size_t)x<<endl;
    cout<<( (size_t)x<<2 )<<endl;
}