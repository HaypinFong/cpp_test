#include<iostream>
using namespace std;
void fast_sort(int arr[],int s,int e){
    if(s >= e)
        return;
    int val(arr[s]);
    int i(s),j(e);
    while(i<j){    // 在i=j的时候已经按val排完序了
        while(i<j){
            if(arr[j] >= val)   // 右边等于的要跳过，保持稳定排序
                j--;
            else
                break;
        }
        // 如果已经有序则j==i退出
        if(i < j){    // 肯定遇到小的了,
            arr[i] = arr[j];
            i++;
        }else   // 已经有序
            break;
        
        while(i<j){
            if(arr[i] < val)   // 左边等于的不能跳过，保持稳定排序，等于的按照大于操作，下轮循环放到右边保持稳定
                i++;
            else
                break;
        }
        // 如果已经有序则i==j退出
        if(i < j){  // 肯定遇到大的或相等的了，既使相等的也要放右边，保持稳定排序
            arr[j] = arr[i];
            j--;
        }
    }
    arr[i]=val; // i==j
    fast_sort(arr,s,i-1);
    fast_sort(arr,i+1,e);
    return;
}
int main(int argc,char* argv[])
{
    int arr[]={3,1,4,1,5,9,2,6};
    size_t len(8);
    fast_sort(arr,0,len-1);
    for(size_t i(0);i<len;i++)
        cout<<arr[i]<<' ';
    cout<<endl;
    return 0;
}