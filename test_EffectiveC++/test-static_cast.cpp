#include "stdio.h"
#include <string>
class TextBlock
{
    public:
    TextBlock()
    {
        printf("call TextBlock()\n");
    }
    TextBlock(const TextBlock& cobj):text(cobj.text)
    {
        printf("call TextBlock(const TextBlock&)\n");
    }
    TextBlock(const char* zeroTerminateStr):text(zeroTerminateStr){}
    const char& operator[](std::size_t position)const
    {
        printf("call const char& operator[]()\n");
        return text[position];
    }
    char& operator[](std::size_t position)
    {
        printf("call char& operator[]()\n");
        char& rtn =  const_cast<char&>(// 去 const，降格
            static_cast<const TextBlock&>(*this)[position]  // 加 const
        );
        printf("type equal: %d\n",typeid(const TextBlock&) == typeid(*this));
        char& rtn2 = const_cast<char&>(// 去 const，降格
            ((const TextBlock&)(*this))[position]   // 加 const，对*this对象执行const TextBlock显式类型转换，升格，是临时行为，不影响*this的类型
        );
        printf("type equal: %d\n",typeid(const TextBlock&) == typeid(*this));
        return rtn2;
    }
    private:
    std::string text;
};
int main(int argc,char* argv[])
{
    auto func1 = []()->void{
        TextBlock obj("haha");
        auto charObj = obj[0];  // 调用非const版本，进而调用const 版本
    };
    func1();
}