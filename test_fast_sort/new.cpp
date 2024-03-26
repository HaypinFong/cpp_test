#include<iostream>
using namespace std;
int combine(int a,int b){
    // int unit_b(0);   // b位数，123是三位
    int b_bak(b);
    int multi(1);
    while(b_bak>0){
        // unit_b += 1;    // >0至少一位
        multi *= 10;
        b_bak /= 10;
    }
    return a*multi+b;
}

float fun(float x){
    return x*x/2.0;
}
float solve(float y){
    float result(-1.0);
    // 二分法
    float s(0.0f),e(1.0f);
    float mid((s+e)/2.0f);
    int sign_fun_s(std::sign(fun(s))),sign_fun_e(std::sign(fun(e)));
    result = fun(mid);
    while(std::abs(result)>1e-6){
        if(std::sign(result)==sign_fun_s)
            s = mid;
        else
            e = mid;
        mid = (s+e)/2.0f;
        result = fun(mid);
    }
    return result;
}

struct ListNode{
    int val;
    ListNode *next;
}
ListNode* inverse(ListNode *head){
    ListNode *p_head(head);
    if(head && head->next && head->next->next){
        // 先考虑三个以上节点：
        ListNode *p_pre(head),*p_cur(head->next),*p_next(head->next->next);
        while(p_next){
            p_cur->next = p_pre;
            p_pre = p_cur;
            p_cur = p_next;
            p_next = p_next->next;
        }
        p_cur->next = p_pre;
        p_head->next = nullptr;
        return p_cur;
    }else if(head && head->next && !head->next->next){
        // 两个节点：
        ListNode *p_second(head->next);
        p_second->next = head;
        head->next = nullptr;
        return p_second;
    }else{
        // 一个节点或者空节点
        return head;
    }
}