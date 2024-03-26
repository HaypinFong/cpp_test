#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
class Test{
    private:
    string m_field;
    public:
    Test(string var):m_field(var){
        static int nCount(0);
        nCount++;
        cout<<"nCount: "<<nCount<<endl;
    };
    void func(){
        static int nCount2(0);  // 实例方法中的局部静态变量也是全局变量，
        nCount2++;
        cout<<"nCount2: "<<nCount2<<endl;
    }
    void test_static_if(bool bvalue){
        if(bvalue){
            static int nCount3(0);
            nCount3++;
            cout<<"nCount3: "<<nCount3<<endl;
        }
    }
    std::string operator()(std::string i,std::string j){
        std::string res(i);
        res += ' ';
        res += j;
        return res;
    }
};
void test_reference(int &a){
    return;
}
int main(int argc,char **argv){
    int a(2);
    test_reference(a);
    Test obj1("heihei"),obj2("haha");
    obj1.func();
    obj2.func();
    obj1.test_static_if(true);
    obj2.test_static_if(true);
    obj1.test_static_if(true);
    std::vector<std::pair<int,std::string> > scans;
    scans.push_back(std::make_pair<int,std::string>(3,"March"));
    scans.push_back(std::make_pair<int,std::string>(2,"February"));
    scans.push_back(std::make_pair<int,std::string>(1,"January"));
    auto comp = [](std::pair<int,std::string> t1,std::pair<int,std::string> t2)->bool{
        return t1.first<t2.first;
    };
    std::sort(scans.begin(),scans.end(),comp);
    for(std::pair<int,std::string> &i:scans)
        cout<<i.first<<' '<<i.second;

    std::vector<int> myv(3);
    cout<<endl<<"myv.size(): "<<myv.size()<<endl;

    Test obj3("lala");
    cout<<obj3("A","B")<<endl;

    int num(-1);
    size_t len(num);
    cout<<"size_t len: "<<len<<endl;
    {
        int num(-1);
        size_t len(num);
        cout<<"size_t len: "<<len<<endl;
    }

    std::vector<int> arr(3,3);
    for(int i(0);i<arr.size();i++)
        cout<<arr[i]<<' ';
    cout<<endl;
}
/**
 * @brief 
 * 输出：
 * nCount: 1
    nCount: 2
 */