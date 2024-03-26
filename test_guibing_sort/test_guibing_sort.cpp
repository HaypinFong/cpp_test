#include<iostream>
#include<vector>
using namespace std;
void guibing_sort(vector<int> &arr,size_t istart,size_t iend){
    if(istart>=iend)
        return;
    size_t imid((istart+iend)*0.5);
    guibing_sort(arr,istart,imid);
    guibing_sort(arr,imid+1,iend);
    // 深度遍历最底层是两个元素
    vector<int> arrtmp(iend-istart+1,0);
    size_t i(istart),j(imid+1);   // index of arr[istart:imid]、arr[imid+1:iend]
    size_t k(0);    // index of arrtmp
    while(i<=imid && j<=iend){
        if(arr[i]<=arr[j])  // 稳定排序，arr[i]=arr[j]时也先压arr[i]
            arrtmp[k++]=arr[i++];
        else
            arrtmp[k++]=arr[j++];
    }
    if(i<=imid){
        while(i<=imid)
            arrtmp[k++]=arr[i++];
    }
    if(j<=iend){
        while(j<=iend)
            arrtmp[k++]=arr[j++];
    }
    for(size_t l(istart),q(0);l<=iend;l++,q++)
        arr[l]=arrtmp[q];
    return;
}
int main(int argc,char *argv[]){
    vector<int> arr={3,1,4,1,5,9,2,6};
    guibing_sort(arr,0,arr.size()-1);
    for(size_t i(0);i<arr.size();i++)
        cout<<arr[i]<<' ';
    cout<<endl;
}