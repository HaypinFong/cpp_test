#include <stdio.h>
#include<string>
#include<iostream>
using namespace std;
int main()
{
   char str[2<<10];
   string sstr("haha");
   size_t t(5);
   sprintf(str, "%s %.2f %d %lu \n heihei\0", sstr.c_str(),3.14159,2,t);
   cout<<str<<endl;
   // string res(str);
   // sstr.append(res);
   sstr.append(str);
   cout<<sstr<<endl;
}