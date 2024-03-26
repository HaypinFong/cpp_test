#include<iostream>
#include<vector>
using namespace std;
void dijkstra(vector<vector<int> >arr,int s,int e){
    // 输入有向图数组arr，起点s(不一定是0)，终点e(不一定是:-1)，打印最近路径
    // 有向图数组元素arr[i][j]>0表示可以从i抵达j，距离为arr[i][j]，arr是方阵
    // 从起点s开始，到s的直连节点，然后是直连节点的直连节点(排除起点s)，最终遍历完所有节点
    vector<pair<int,float> >table(arr.size(),make_pair(-1,1<<30)); // 起点不动
    vector<int> nodes; // 收集直连节点，按顺序，每个直连节点只考察一次
    // 先确定起点的直连节点并初始化table
    for(int i(0);i<arr.size();i++){
        if(arr[s][i]>0){
            nodes.push_back(i);
            table[i] = makr_pair(s,arr[s][i]);
        }
    }
    for(vector<int>::iterator inode(nodes.begin());
        inode!=nodes.end();inode++){
        for(int i(0);i<arr.size();i++){ // 考察直连节点*inode的直连节点i
            // 收集直连节点
            if(arr[*inode][i]>0 && i!=s && nodes.find(i)==nodes.end())
                nodes.push_back(i);
            if(arr[*inode][i]>0){   // 直连
                // 需要对比里程长度
                float len(tables[*inode].second+arr[*inode][i]);
                if(table[i].first>0 && table[i].second > len){
                    // 已经有路径，对比路程，*inode的累积里程加上*inode->i的路程
                    table[i] = makr_pair(*inode,len);
                }else if(table[i].first<0){
                    // i节点还没有路径，直接填充
                    table[i] = makr_pair(*inode,len);
                }
            }
        }
    }
    // 输出路径
    int inode(e);
    while(inode>=s){
        cout<<inode<<'<-';
        inode = table[inode].first;
    }
}
int main(int argc,char **argv){
    // vector<int> nodes;
    // auto ite = nodes.push_back(2);
    // cout<<ite.first<<' '<<ite.second<<endl;
}