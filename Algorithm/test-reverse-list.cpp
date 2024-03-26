#include<iostream>
using namespace std;
class Node
{
    public:
    Node(int v):value(v){};
    void set_next(Node* node){
        if(node)
            next = node;
    }
    int value;
    Node* next;
};

Node* reverse_list(Node* root)
{
    if(root == nullptr || root->next == nullptr)
        return root;
    Node *ppre,*pcur,*pnext;
    ppre = root;
    pcur = root->next;
    while(pcur->next)
    {
        pnext = pcur->next;
        pcur->next = ppre;

        ppre = pcur;
        pcur = pnext;
    }
    pcur->next = ppre;
    root->next = nullptr;
    return pcur;
}

void print_list(Node* root)
{
    while(root)
    {
        cout<<root->value<<' ';
        root = root->next;
    }
    cout<<endl;
}

#define COUNT 5
int main(int argc,char* argv[])
{
    Node * list[COUNT];
    for(int i = 0;i<COUNT;i++)
        list[i] = new Node(i);
    for(int i = 0;i<COUNT -1 ;i++)
        list[i]->set_next(list[i+1]);
    print_list(list[0]);

    Node* root_new = reverse_list(list[0]);
    print_list(root_new);
}