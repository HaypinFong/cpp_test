#include<iostream>
using namespace std;
void Foo1(int arr[100]){ 
    cout << "pass by pointer:   " << sizeof(arr) << endl;
}
void Foo2(int (&arr)[100]){ 
    cout << "pass by reference: " << sizeof(arr) << endl;
}
void main(){ 
    int a[100]; 
    cout << "In main function : " << sizeof(a) << endl; 
    Foo1(a); 
    Foo2(a); 
}