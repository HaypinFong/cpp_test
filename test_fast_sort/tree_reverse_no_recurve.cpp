#include<iostream>
#include<stack>
using namespace std;
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
}
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res; 
        if(root == NULL)
            return res;
        //辅助栈
        stack<TreeNode*> s; 
        //根节点先进栈
        s.push(root); 
        //直到栈中没有节点
        while(!s.empty()){  // 递归也是循环的体现，递归是输入(node)发生变化的循环
            //每次栈顶就是访问的元素
            TreeNode* node = s.top();
            s.pop();
            res.push_back(node->val);   // 先序遍历
            //如果右边还有右子节点进栈
            if(node->right) 
                s.push(node->right);
            //如果左边还有左子节点进栈
            if(node->left) 
                s.push(node->left);
        }
        return res;
    }
};
