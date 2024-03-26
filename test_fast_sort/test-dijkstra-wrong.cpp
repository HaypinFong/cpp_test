#include<iostream>
#include<vector>
#include<set>
using namespace std;
/*
不对
               s                   e
               0   1   2   3   4   5
0  arr[][] = {{0   6   3            }   
1             {6   0   2   5        }   
2             {3   2   0   3   4    }   
3             {    5   3   0   2   3}   
4             {        4   2   0   5}   
5             {            3   5   0}   
图见https://blog.csdn.net/Xing_LG/article/details/124864695
从起点0出发，直达节点是1,2，考察1,2，(上一节点,累计路径)分别为(0,6),(0,3)
从1,2出发，直达节点是3,4，考察3,4，(上一节点,累计路径)分别为(2,6),(2,7)
从3,4出发，直达节点是5，考察5，(上一节点,累计路径)为(3,9)
路径5-3-2-0
*/
struct Item
{
    int pre_node;
    float cost_total;
    Item()
    {
        pre_node = -1;
        cost_total = -1.0;
    }
};
float dijkstra(float* arr[],int len,int s,int e)
{
    vector<Item> table(len);
    set<int> nodes_unresolved;  // 从起点出发
    for(int i = 0;i<len;i++)
        nodes_unresolved.insert(i);
    nodes_unresolved.erase(s);
    vector<int> nodes_direct;
    // init
    table[s].cost_total = 0;
    for(int i = s+1;i<len;i++)
        if(arr[s][i]>0) // 里程用-1表示不可达
        {   
            nodes_direct.push_back(i);
            nodes_unresolved.erase(i);
            table[i].pre_node = s;
            table[i].cost_total = arr[s][i];
        }
    // loop
    while(nodes_direct.size()>0)
    {
        // update 
        for(const int & node:nodes_direct)
        {

        }
    }
}