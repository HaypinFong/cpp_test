#include<iostream>
#include<vector>
/*
2.	给定两个递增排序数组，arr1 = {1，1，2，2，4，4，5，5，6，6，7，7}
和arr2 = {-90，-85，-85，-85，0，1，3，90}，使用C/C++语言编写一个函数
合并这两个数组，并保证合并后的数组也是递增排序的。

3.	使用C++语言通过指针的方式，将字符串“BALYQ4321BALYQ”逆序输出。*/
using namespace std;
vector<int> merge(vector<int> arr1,vector<int> arr2){
    vector<int> arrnew(arr1.size()+arr2.size(),0);  // 已知大小一次申请，避免扩容
    int i(0),j(0),k(0); // k是arrnew下标
    while(i<arr1.size() && j<arr2.size()){
        if(arr1[i]<=arr2[j]) // 相等先压栈arr1，看业务需求
            arrnew[k++] = arr1[i++];
        else
            arrnew[k++] = arr2[j++];
    }
    if(i<arr1.size()){  // arr2耗尽，收集arr1
        while(i<arr1.size())
            arrnew[k++] = arr1[i++];
    }else{  // arr1耗尽，收集arr2
        while(j<arr2.size())
            arrnew[k++] = arr2[j++];
    }
    return arrnew;
}
void reverse_str(char *str){
    char *pstrhead(str),*pstrend(str);
    while((*pstrend)!='\0') {  // 可以用栈收集元素最后出栈打印，这里说通过指针的方式那就只用指针吧
        pstrend++;
    }
    // 逆序打印
    pstrend--;
    while(pstrend!=pstrhead){
        cout<<(*pstrend);
        pstrend--;
    }
    cout<<(*pstrend)<<endl;
}
int main(int argc,char** argv){
    char *str = "abc";
    cout<<(str[3]=='\0')<<endl;
    vector<int> arr1(12,0),arr2(8,0);
    arr1[0] = 1;arr1[1]=1;arr1[2]=2,arr1[3]=2;arr1[4]=4;arr1[5]=4,arr1[6]=5;
    arr1[7]=5;arr1[8]=6;arr1[9]=6;arr1[10]=7;arr1[11]=7;
    arr2[0] = -90;arr2[1]=-85;arr2[2]=-85,arr2[3]=-85;arr2[4]=0;arr2[5]=1;
    arr2[6]=3;arr2[7]=90;
    vector<int> arrnew(merge(arr1,arr2));
    for(int i(0);i<arrnew.size();i++)
        cout<<arrnew[i]<<' ';
    cout<<endl;
    char *str2 = "BALYQ4321BALYQ";
    reverse_str(str2);
}