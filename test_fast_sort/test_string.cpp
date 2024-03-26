#include<iostream>
#include<string>
using namespace std;
int main(int argc,char **argv){
    string str("on  11");
    int ispace1(str.find_first_of(' ')),ispace2(str.find_last_of(' '));
    cout<<str.substr(0,ispace1-0)<<endl;
    cout<<str.substr(ispace2+1)<<endl;
}