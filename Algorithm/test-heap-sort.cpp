#include<iostream>
using namespace std;
/*
len = 4，最后一个非叶子节点下标(int)(len-1)/2
        0
    1       2
3     _  _      _

len = 5，最后一个非叶子节点下标(int)(len-1)/2
        0
    1       2
3      4 _      _

len = 6，最后一个非叶子节点下标(int)(len-1)/2
            0
        1       2(i)
    3     4   5(i*2+1)  6((i+1)*2)
7     8 _
*/
bool heap_sort(int arr[],int len)
{
    if(len <= 1)
        return true;
    int i = (int)(len-1)/2; // 最后一个非叶子节点下标
    while(i>=0)
    {
        int ileft = i*2+1, iright = (i+1)*2;
        if(iright<len && arr[i]<arr[iright]) // 有右子节点，不swap想等元素就是保持原位了
            std::swap(arr[i],arr[iright]);
        if(ileft<len && arr[i]<arr[ileft])  // 有左子节点
            std::swap(arr[i],arr[ileft]);
        i--;
    }
    std::swap(arr[0],arr[len-1]);
    heap_sort(arr,len-1);
    return true;
}
#define COUNT 8
int main(int argc,char* argv[])
{
    int arr[] = {3,1,4,1,5,9,2,6};
    heap_sort(arr,COUNT);
    for(int i=0;i<COUNT;i++)
        cout<<arr[i]<<' ';
    cout<<endl;
}