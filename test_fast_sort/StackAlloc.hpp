// StackAlloc.hpp

#ifndef STACK_ALLOC_H
#define STACK_ALLOC_H

#include <memory>

template <typename T>
struct StackNode_
{
  T data;
  StackNode_* prev;
};

// T 为存储的对象类型, Alloc 为使用的分配器,
// 并默认使用 std::allocator 作为对象的分配器
template <class T, class Alloc = std::allocator<T> >
class StackAlloc    // 链表栈容器
{
  public:
    // 使用 typedef 简化类型名
    typedef StackNode_<T> Node;
    typedef typename Alloc::template rebind<Node>::other allocator;

    // 默认构造
    StackAlloc() { head_ = 0; }
    // 默认析构
    ~StackAlloc() { clear(); }

    // 当栈中元素为空时返回 true
    bool empty() {return (head_ == 0);}

    // 释放栈中元素的所有内存
    void clear() {
      Node* curr = head_;
      while (curr != 0)
      {
        Node* tmp = curr->prev;
        allocator_.destroy(curr); // 调用Node析构
        allocator_.deallocate(curr, 1); // “释放”curr堆内存，起始没有调用delete，只是将该内存槽标记为空闲
        curr = tmp;
      }
      head_ = 0;
    }

    // 入栈
    void push(T element) {
      // 为一个节点分配内存
      Node* newNode = allocator_.allocate(1); // 先从内存池“分配”内存，
      // 调用节点的构造函数
      allocator_.construct(newNode, Node());  // 在指针newNode处调用拷贝构造

      // 入栈操作
      newNode->data = element;
      newNode->prev = head_;
      head_ = newNode;
    }

    // 出栈
    T pop() {
      // 出栈操作 返回出栈结果
      T result = head_->data;
      Node* tmp = head_->prev;
      allocator_.destroy(head_);        // 析构
      allocator_.deallocate(head_, 1);  // “释放”head_堆内存
      head_ = tmp;
      return result;
    }

    // 返回栈顶元素
    T top() { return (head_->data); }

  private:
    allocator allocator_;
    Node* head_;
};

#endif // STACK_ALLOC_H