#include<iostream>
using namespace std;
bool compare(int &a,int &b){
    return a<b;
}
void fast_sort(int arr[],int istart,int iend,bool compare(int&,int&)){
    if(istart>=iend)    return;
    int nmid(arr[istart]);
    int i(istart),j(iend);  // 合适的arr[j]要填至arr[i]，arr[i]初始就是nmid，本次递归均与nmid对比
    while(i<j){     // 左右开弓可能需要若干轮
        while(i<j){ // 左移j不能超过i，相等时刻就是本次递归结束时刻
            if(compare(arr[j],nmid)){
                arr[i]=arr[j];  // 填arr[i]坑，arr[i]要么是nmid已经保存，要么已经填到右边某arr[j]而空出来
                i++;    // i一侧下次考察的起始下标
                break;
            }
            j--;
        }
        while(i<j){
            if(!compare(arr[i],nmid)){
                arr[j]=arr[i];  // 填到上面空出来的arr[j]
                j--;    // j一侧下次考察的起始坐标
                break;
            }
            i++;
        }
    }
    arr[i]=nmid;    // i==j，该唯一空出来的arr[j]或arr[i]就是中间的nmid
    fast_sort(arr,istart,i-1,compare);
    fast_sort(arr,i+1,iend,compare);
}
void print_arr_ptr(int (*parr)[8]){     // 1、“名义上”是指向数组的指针，实参得是&arr，实际上仍是指向数组首元素的指针，同时传入实参数组维数必须一致！
    cout<<"parr "<<parr<<endl;
    cout<<"*parr "<<*parr<<endl;
}
void print_arr_ref(int (&rarr)[8]){     // 2、传入实参数组维数必须一致
    cout<<"rarr "<<rarr<<endl;
}
int main(int argc,char **argv){
    int arr[]={3,1,4,1,5,9,2,6};
    int len(7);
    fast_sort(arr,0,len,compare);
    for(int i(0);i<=len;i++)
        cout<<arr[i]<<' ';      // *(arr+i)
    cout<<endl;
    cout<<"arr "<<arr<<endl;    // 0x7ff7bfeff000
    print_arr_ptr(&arr);
    print_arr_ref(arr);
    for(int i(0);i<=len;i++)
        cout<<i[arr]<<' ';      // *(i+arr)，C数组真的只是数组指针(整数)i+偏移量(整数)arr
    cout<<endl;
}