/**
 * https://blog.csdn.net/YiYeZhiNian/article/details/122217450
 * https://blog.csdn.net/Xing_LG/article/details/124864695
 * 
               s                   e
               0   1   2   3   4   5
0  arr[][] = {{0   6   3   N   N   N}   
1             {6   0   2   5   N   N}   
2             {3   2   0   3   4   N}   
3             {N   5   3   0   2   3}   
4             {N   N   4   2   0   5}   
5             {N   N   N   3   5   0}  

1.指定一个节点，例如我们要计算 ‘A’ 到其他节点的最短路径

2.引入两个集合（S、U），S集合包含已求出的最短路径的点（以及相应的最短长度），U集合包含未求出最短路径的点（以及A到该点的路径，注意 如上图所示，A->C由于没有直接相连 初始时为∞）

3.初始化两个集合，S集合初始时 只有当前要计算的节点，A->A = 0，U集合初始时为 A->B = 4, A->C = ∞, A->D = 2, A->E = ∞，敲黑板！！！接下来要进行核心两步骤了

4.从U集合中找出路径最短的点，加入S集合，例如 A->D = 2

5.更新U集合路径，if ( ‘D 到 B,C,E 的距离’ + ‘AD 距离’ < ‘A 到 B,C,E 的距离’ ) 则更新U

6.循环执行 4、5 两步骤，直至遍历结束，得到A 到其他节点的最短路径
*/
#include<vector>
#include<functional>
using namespace std;

struct Node
{
    int node;
    int pre_node;
    float cost_accumulate;
    Node(int _self,int _pre,float cost = INT32_MAX):
        node(_self)
        ,pre_node(_pre)
        ,cost_accumulate(cost){};
};
bool dijkstra(const vector<vector<float> >& arr,int len,int s,int e)
{
    // 0<= s<e <len
    vector<Node> nodes_resolved,nodes_unresolved;
    nodes_resolved.push_back({s,s,0});
    // init cost ultimate
    for(int i = 0;i<len;i++)
        if(i!=s)
            nodes_unresolved.push_back({i,s,INT32_MAX});
    // loop
    while(nodes_unresolved.size()>0)
    {
        float cost_min = INT32_MAX; // among nodes_unnresolved
        vector<Node>::iterator node_nearst = nodes_unresolved.end();
        for(vector<Node>::iterator ite = nodes_unresolved.begin();ite!=nodes_unresolved.end();ite++)
        {
            Node& cur = *ite;
            for(const Node& pre:nodes_resolved)
            {
                float cost = pre.cost_accumulate+arr[pre.node][cur.node];
                if(cost < cur.cost_accumulate)
                {
                    cur.pre_node = pre.node;
                    cur.cost_accumulate = cost;
                }
            }
            if(cur.cost_accumulate < cost_min)
            {
                cost_min = cur.cost_accumulate;
                node_nearst = ite;
            }
        }
        nodes_resolved.push_back(*node_nearst);
        nodes_unresolved.erase(node_nearst);
    }
    // result
    // nodes_resolved排好序直接回溯取路径
    auto compare = [](const Node& l,const Node& r)->bool
    {
        return l.node < r.node;    
    };
    std::sort(nodes_resolved.begin(),nodes_resolved.end(),compare);
    int i = e;
    while(i!=s)
    {
        printf("%d ",i);
        i = nodes_resolved[i].pre_node;
    }
    printf("%d\t\n",i);
    return true;
}
#define N INT16_MAX
int main(int argc,char* argv[])
{
    int len = 6;
    vector<vector<float> >arr(len);
    //      0 1 2 3 4 5
    arr = {{0,6,3,N,N,N},  // 0
           {6,0,2,5,N,N},  // 1
           {3,2,0,3,4,N},  // 2
           {N,5,3,0,2,3},  // 3
           {N,N,4,2,0,5},  // 4
           {N,N,N,3,5,0}}; // 5
    dijkstra(arr,len,0,5);
}