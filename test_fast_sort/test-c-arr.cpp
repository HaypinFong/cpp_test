#include "stdio.h"
class Foo
{
    //static int len;
    //int arr[len];   //  error: fields must have a constant size: 'variable length array in structure' extension will never be supported
    static const int len = 3;
    int arr[len];
    enum ARRAY_LEN{LEN = 5};
    int arr2[LEN];
};
int main(int argc,char* argv[])
{

}