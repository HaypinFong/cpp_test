#include<iostream>
#include<string>
using namespace std;
int main(int argc, char **argv)
{
    std::string seps("haha heiehi \n ohoh");
    std::stringstream str(seps);
    seps.clear();
    while(str>>seps){
        cout<<seps<<endl;
    }
}