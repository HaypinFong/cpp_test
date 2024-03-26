#include <iostream>
#include <vector>
using namespace std;
void fast_sort(vector<int> &arr_idx,const vector<int> &arr_val,int istart,int iend)
{   /*
    仍然是快排，经典快排是比较输入数组自身的值，
    这里比较输入的下标数组arr_idx对应到值数组arr_val中的值而已
    */
    if(istart<0 || iend<0 || istart>=iend)
        return;
    int val_idx(arr_idx[istart]);
    int is(istart),ie(iend);
    while(is<ie){
        while(is<ie){
            if(arr_val[arr_idx[ie]]<arr_val[val_idx])
                break;
            else
                ie--;
        }
        if(is<ie)
            arr_idx[is++] = arr_idx[ie];
        while(is<ie){
            if(arr_val[arr_idx[is]]>arr_val[val_idx])
                break;
            else
                is++;
        }
        if(is<ie)
            arr_idx[ie--] = arr_idx[is];
    }
    arr_idx[is] = val_idx;
    fast_sort(arr_idx,arr_val,istart,is-1);
    fast_sort(arr_idx,arr_val,is+1,iend);
}
bool sortByHeight(int num,vector<int> heights,vector<int> weights,vector<int> &orders)
{
    orders.clear();
    if(num!=heights.size() || num!=weights.size())
        return false;
    orders.resize(num);
    for(int i;i<num;i++)
        orders[i] = i;
    fast_sort(orders,heights,0,num-1);
    fast_sort(orders,weights,0,num-1);
    return true;
}
int main(int argc,char *argv[])
{
    // https://mp.weixin.qq.com/s/WnroOmuReFZRiQJWAEkt0w
    vector<int> heights={100,100,120,130};
    vector<int> weights={40,30,60,50};
    vector<int> orders;
    sortByHeight(4,heights,weights,orders);
    for(int i;i<orders.size();i++)
        cout<<orders[i]<<' ';
    cout<<endl;

    //cout<<(2.5**2)<<endl;
    cout<<std::pow(10,17)<<endl;
}