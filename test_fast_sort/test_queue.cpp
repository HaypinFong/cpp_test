#include<iostream>
#include<deque>
using namespace std;
int test_queue(){
    deque<int> my_deque{3,1,4,5,9,2,6};
    auto ifirst(my_deque.begin());
    auto isecond(my_deque.begin()+1);
    cout<<*isecond<<endl;
    cout<<*(my_deque.begin())<<endl;
    my_deque.pop_front();
    cout<<*isecond<<endl;
    cout<<*(my_deque.begin())<<endl;
    cout<<"*ifirst "<<*ifirst<<endl;

    deque<int> my_deque2{3,1,4,5,9,2,6};
    ifirst = my_deque2.begin();
    for(int i(0);i<4;i++)
        my_deque2.pop_front();
    cout<<*ifirst<<endl;
}
int main(int argc,char **argv){
    test_queue();
}