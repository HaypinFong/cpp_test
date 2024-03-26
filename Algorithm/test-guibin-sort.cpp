#include "stdio.h"
void guibin_sort(int arr[],int s,int e)
{
    if(s>=e)
        return;
    int mid = (s+e)*0.5;
    guibin_sort(arr,s,mid);
    guibin_sort(arr,mid+1,e);
    int len = e-s+1;
    int arr_temp[len];
    int i=s,j=mid+1,k=0;
    while(i<=mid && j<=e)
    {
        if(arr[i]<=arr[j])  // 升序排序，稳定，相等时左边在前
            arr_temp[k++] = arr[i++];
        else
            arr_temp[k++] = arr[j++];
    }
    // 补充
    if(i>mid)
        while(j<=e)
            arr_temp[k++] = arr[j++];
    else
        while(i<=mid)
            arr_temp[k++] = arr[i++];
    // 回填
    for(int m = 0;m<len;m++)
        arr[s+m] = arr_temp[m];
}
int main(int argc,char* argv[])
{
    int arr[]={3,1,4,1,5,9,2,6};
    int len = sizeof(arr)/sizeof(arr[0]);
    guibin_sort(arr,0,len-1);
    for(int i = 0;i<len;i++)
        printf("%d ",arr[i]);
    printf("\n");
}