#include <string>
#include <sstream>
#include <type_traits>
using namespace std;

template<typename ... Args>
string string_format(const string& format, Args ... args){
    size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);  // Extra space for \0
    // unique_ptr<char[]> buf(new char[size]);
    char bytes[size];
    snprintf(bytes, size, format.c_str(), args ...);
    return string(bytes);
}

template<typename T,typename U>
constexpr bool is_decay_que = std::is_same_v<std::decay_t<T>,U>;

template<typename T>
std::string getBriefStringOfFloat(T num)
{
    std::ostringstream oss;
    oss<<num;
    if( is_decay_que<T,float> || is_decay_que<T,double>)
    {
        if(oss.str().find('.')==std::string::npos)
        {
            char numStr[256];
            sprintf(numStr,"%.1f",(double)num);
            return numStr;
        }
    }
    return oss.str();
}
int main(int argc,char* argv[])
{
    printf(string_format("%f\n",3.1410000).c_str());

    double num=32.0100; 
    std::ostringstream oss; 
    oss<<num; 
    printf("%s\n",oss.str().c_str()); 

    char str[256];
    sprintf(str,"%.2f\n",3);
    printf("%s\n",str);
    printf("%.1f\n",(double)3);

    printf("%s\n",getBriefStringOfFloat(32.010000).c_str());
    printf("%s\n",getBriefStringOfFloat(32.0).c_str());
}