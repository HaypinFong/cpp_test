#include<iostream>
#include<functional>
using namespace std;
bool compare(int &a,int &b){
    return a<b;
}
// void heap_sort(int (&arr)[8],int istart,int iend,bool (*compare)(int&,int&)){
void heap_sort(int (&arr)[8],int istart,int iend,std::function<bool (int&,int&)> compare){
    if(istart>=iend)    return;
    for(int i(iend);i>istart;i--){
        if(compare(arr[i-istart],arr[(i-istart+1)/2-1]))
            std::swap(arr[i-istart],arr[(i-istart+1)/2-1]);
    }
    std::swap(arr[istart],arr[iend]);
    heap_sort(arr,istart,iend-1,compare);
}
int main(int argc,char **argv){
    int arr[]={3,1,4,1,5,9,2,6};
    int len(7);
    heap_sort(arr,0,len,compare);
    for(int i(0);i<=len;i++)
        cout<<arr[i]<<' ';
    cout<<endl;

    int row(3),col(3);
    float **Npi = new float*[row];
    for(int i(0);i<row;i++)
        Npi[i] = new float[col];
    for(int i(0);i<row;i++){
        for(int j(0);j<col;j++)
            cout<<Npi[i][j]<<' ';
        cout<<endl;
    }
    for(int i(0);i<row;i++)
        delete[] Npi[i];
    delete[] Npi;


}