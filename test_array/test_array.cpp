#include <array>
using namespace std;
class Type
{
    public:
    int val;
};
int main(int argc,char* argv[])
{
    array<Type,3> arr;
    arr[0].val = 0;
    arr[1].val = 1;
    printf("%d\n",arr.size());
}