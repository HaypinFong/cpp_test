/**
 * https://blog.csdn.net/coolwriter/article/details/80970718
*/
#include <iostream>
#include "printf.h"
#include <vector>
#include <string>

using namespace std;
class T
{
    public:
    string val;
    string get_val(){return val;}
    T(string _val):val(_val){}
    T(T& other)
    {
        // copy constructor
        printf("call T(T&{%s})\n",other.get_val().c_str());
    }

    T(T&& other)
    {
        // move constructor
        printf("call T(T&&{%s})\n",other.get_val().c_str());
    }
};



int main()
{
    T A("abc");
    T&& Rval = std::move(A);
    T B(Rval);    // this is a copy , not move.
    cout << A.get_val() << endl;   // output "abc"
    T C(std::forward<T>(Rval));  // move.
    cout << A.get_val() << endl;       /* output "" */
    return 0;

    /**
     * 
    */
}