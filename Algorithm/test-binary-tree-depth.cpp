#include "stdio.h"
/**
 * compute binary-tree's depth
*/
struct Node
{
    Node(int _val = 0,Node* pl=nullptr,Node* pr=nullptr):val(_val),pLeft(pl),pRight(pr){}
    int val;
    Node* pLeft;
    Node* pRight;
};
void get_binary_tree_depth_recursive(Node* node,int depth_node,int& depth)
{   // 先序遍历
    if(!node) return;
    if(depth<depth_node)
        depth = depth_node;
    if(node->pLeft)
        get_binary_tree_depth_recursive(node->pLeft,depth_node+1,depth);
    if(node->pRight)
        get_binary_tree_depth_recursive(node->pRight,depth_node+1,depth);
}
int get_binary_tree_depth(Node* node)
{
    
}
int main(int argc,char* argv[])
{
    auto func1 = []()->void{
        Node n1{1},n2{2,&n1},n3{3},n4{4,&n3,&n2},n5{5},n6{6,&n5},n7{7,&n6,&n4};
        int depth = 1;
        get_binary_tree_depth_recursive(&n7,1,depth);
        printf("depth: %d\n",depth);
    };
    func1();
}