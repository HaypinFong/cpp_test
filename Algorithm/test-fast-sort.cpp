#include<iostream>
using namespace std;
bool fast_sort(int arr[],int start,int end)
{
    if(start >= end)
        return true;
    int val = arr[start];
    int i = start,j = end;
    while(i<j)
    {
        while(i<j && arr[j] >= val) // ==的保持原位排序
            j--;
        if(i<j)
            arr[i++] = arr[j];
        while(i<j && arr[i] < val)  // ==的也要向后移动，保持原位排序
            i++;
        if(i<j)
            arr[j--] = arr[i];
    }
    arr[i] = val;
    fast_sort(arr,start,i);
    fast_sort(arr,i+1,end);
    return true;
}
#define COUNT 7
int main(int argc,char* argv[])
{
    int arr[] = {3,1,4,1,5,9,2,6};
    fast_sort(arr,0,COUNT);
    for(int i = 0;i<COUNT;i++)
        cout<<arr[i]<<' ';
    cout<<endl;
}