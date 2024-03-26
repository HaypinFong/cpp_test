#include<iostream>
#include<string>
#include<utility>
using namespace std;
void test_right_refer(){
    string str("haha");
    string && rrstr = std::move(str);
    cout<<rrstr<<endl;
    cout<<str<<endl;
}
int main(int argc,char *argv[]){
    test_right_refer();
}