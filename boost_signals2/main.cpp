#include "boost/signals2.hpp"
#include<iostream>
using namespace std;
struct Hello{
    void operator()()const{
        cout<<"Hello";
    }
};
struct World{
    void operator()()const{
        cout<<",World"<<endl;
    }
};
int main(int argc,char* argv[]){
    boost::signals2::signal<void()> sig;
    Hello hello;
    World world;
    sig.connect(hello);
    sig.connect(world);
    sig();
}