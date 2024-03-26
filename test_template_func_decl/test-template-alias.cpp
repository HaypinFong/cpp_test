#include "stdio.h"
#include <string>
using namespace std;
template<typename T1,typename T2> using twin = pair<T1,T2>;
int main(int argc,char* argv[])
{
    twin<char,string> table;
    table = std::make_pair('a',"aha");
    printf("%c %s\n",table.first,table.second.c_str()); // a aha
}