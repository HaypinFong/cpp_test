#ifndef MEMORY_POOL_HPP
#define MEMORY_POOL_HPP

#include <climits>
#include <cstddef>

template <typename T, size_t BlockSize = 4096>  // 模板类型也是一种参数，模板变量BlockSize也是一个参数
class MemoryPool  // 用于容器的内存分配器类
{
  private:
    // 用于存储内存池中的对象槽
    union Slot_ {   // 链表节点类型
      T element;    // 链表节点数据
      Slot_* next;  // 链表节点指针
    };

    // 数据指针
    typedef char* data_pointer_;  // 指向1个字节的指针
    // 对象槽
    typedef Slot_ slot_type_;     // 链表节点类型
    // 对象槽指针
    typedef Slot_* slot_pointer_; // 链表节点指针，指向Slot_，即要么指向T实例，要么指向Slot_*

    // 指向当前内存区块
    slot_pointer_ currentBlock_;
    // 指向当前内存区块的一个对象槽
    slot_pointer_ currentSlot_;
    // 指向当前内存区块的最后一个对象槽
    slot_pointer_ lastSlot_;
    // 指向当前内存区块中的空闲对象槽
    slot_pointer_ freeSlots_;
    // 检查定义的内存池大小是否过小，不同于 assert 是在运行期对错误进行检查， static_assert 是在编译期对表达式进行判断，并打印出具体的出错信息。
    static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too small.");
  public:
    // 使用 typedef 简化类型书写
    typedef T*              pointer;  // 链表节点数据指针，指向T实例的指针

    // 定义 rebind<U>::other 接口
    template <typename U> struct rebind { // 模板类
      typedef MemoryPool<U> other;  // 类型数据成员，rebind绑定模板类型U的内存分配器类
    };

    // 默认构造
    // C++11 使用了 noexcept 来显式的声明此函数不会抛出异常
    MemoryPool() noexcept { // 使默认构造函数不抛出异常
      currentBlock_ = nullptr;
      currentSlot_ = nullptr;
      lastSlot_ = nullptr;
      freeSlots_ = nullptr;
    }

    // 销毁一个现有的内存池
    ~MemoryPool() noexcept {
      // 循环销毁内存池中分配的内存区块
      slot_pointer_ curr = currentBlock_; // 栈顶链表节点指针
      while (curr != nullptr) {
        slot_pointer_ prev = curr->next;
        operator delete(reinterpret_cast<void*>(curr));
        curr = prev;
      }
    }

    // 同一时间只能分配一个对象, n 和 hint 会被忽略
    pointer allocate(size_t n = 1, const T* hint = 0) { // 分配器要实现allocate()方法，分配一个T元素的内存
      if (freeSlots_ != nullptr) { // 每次调用allocate()只分配一个元素的内存槽，freeSlots_非零表示空闲内存槽链表至少有一个内存槽
        pointer result = reinterpret_cast<pointer>(freeSlots_); // Slot_*转T*，Slot_*要么是T*要么是Slot_**，Union
        freeSlots_ = freeSlots_->next;
        return result;  /* 分配一个T元素的内存，返回T*，外部作用域将对T*填充数据(将覆盖next，也不需要保留next了
        ，分配器类只负责分配内存，链表结构的连接信息由容器类StackAllock记录)，内存槽未被使用时
        只存储有下一内存槽的地址构成“空闲内存槽地址链表”，freeSlots_链表表示空闲内存槽指针链表，
        但其Slot_*节点却是"连续存储"的，与T共享内存，空闲时只存储下一个空闲T内存段的指针Slot_* next
        ，如果被分配出去就返回T*，并更新freeSlots_到链表的下一个内存槽(段)指针Slot_*
        */
      }
      else {  // 没有空闲内存槽，要补充申请内存区块
        if (currentSlot_ >= lastSlot_) {  
          // 申请栈内存向小增长，申请堆内存向大增长，但不论栈内存块还是堆内存块内部都是增加方向，如果当前内存槽超过尾内存槽则需要补充申请内存区块
          // 分配一个内存区块
          data_pointer_ newBlock = reinterpret_cast<data_pointer_>(operator new(BlockSize));  // 新内存块的起始地址
          reinterpret_cast<slot_pointer_>(newBlock)->next = currentBlock_;  // 将补充申请的内存区块的首元素与上一内存区块的currentBlock_连接，上一内存区块的currentBlock_应该已经填充T数据，
          currentBlock_ = reinterpret_cast<slot_pointer_>(newBlock);  // newBlock为当前元素内存槽起始地址
          data_pointer_ body = newBlock + sizeof(slot_pointer_);  // 起始地址+Slot_*指针的4个字节
          uintptr_t result = reinterpret_cast<uintptr_t>(body);
          size_t bodyPadding = (alignof(slot_type_) - result) % alignof(slot_type_);  // Slot_联合类型的对齐字节数-
          currentSlot_ = reinterpret_cast<slot_pointer_>(body + bodyPadding); // newBlock+sizeof(slot_pointer_)+bodyPadding，即newBlock跳过一个Slot_元素后的地址作为currentBlock_
          lastSlot_ = reinterpret_cast<slot_pointer_>(newBlock + BlockSize - sizeof(slot_type_) + 1); // newBlock+(BlockSize-sizeof(slot_type)+1)
        }
        return reinterpret_cast<pointer>(currentSlot_++);
      }
    }

    // 销毁指针 p 指向的内存区块
    void deallocate(pointer p, size_t n = 1) {
      if (p != nullptr) {
        reinterpret_cast<slot_pointer_>(p)->next = freeSlots_;  // 将要释放的指针p串联到freeSlots_，使指针p指向freeSlots_顶
        freeSlots_ = reinterpret_cast<slot_pointer_>(p);        // 要释放的指针p作为当前freeSlots_，就不释放内存了，只标记为空闲内存即可，直接用于分配
      }
    }

    // 调用构造函数, 使用 std::forward 转发变参模板
    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
      new (p) U (std::forward<Args>(args)...);  // 在p位置调用U构造函数
    }

    // 销毁内存池中的对象, 即调用对象的析构函数
    template <typename U>
    void destroy(U* p) {
      p->~U();
    }

  
};

#endif // MEMORY_POOL_HPP