#include "stdio.h"
#include <vector>
using namespace std;
int main(int argc,char* argv[])
{
    auto func1 = []()->void{
        vector<int> arr,temp{3,4,5};
        arr.reserve(temp.size());
        arr.insert(arr.end(),temp.begin(),temp.end());
        arr.resize(temp.size());
        for(auto i:arr)
            printf("%d ",i);
        printf("\n");
    };
    func1();
}