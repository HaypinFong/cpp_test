#include<iostream>
#include<map>
#include<string>
using namespace std;
pair<int,string> get_pair(pair<const int,string> &pair){  // 左值引用
    return pair;
}
pair<int,string> get_pair2(pair<int,string> &pair){  // 左值引用
    return pair;
}
pair<string,string> get_pair3(pair<string,string> &pair){
    return pair;
}
pair<string,string> get_pair4(pair<const string,string> &pair){
    return pair;
}
int main(int argc,char **argv){
    map<const int,string> mymap;
    mymap[1]="one";
    mymap[2]="two";
    map<int,string> mymap2;
    mymap[1]="one";
    mymap[2]="two";
    cout<<( (std::string)typeid(*mymap.begin()).name()
    ==(std::string)typeid(*mymap2.begin()).name() )<<endl;  // 1
    // for(pair<int,string> &ipair:mymap2){
    //     /*error: non-const lvalue reference to type 'pair<int, [...]>' 
    //     cannot bind to a value of unrelated type 'pair<const int, [...]>'
    //     即此时mymap2范围for循环的类型变成pair<const int,string>了，
    //     范围for循环map将返回键是const的pair<const T,T_value>
    //     */
    //     get_pair2(ipair);
    // }
    for(pair<const int,string> &ipair:mymap2){  // ok
        get_pair(ipair);
    }


    map<string,string> mymap3;
    mymap3["january"]  = "yi";
    mymap3["february"] = "er";
    // for(pair<string,string> &ipair:mymap3){
    for(pair<const string,string> &ipair:mymap3){
        /*
        error: non-const lvalue reference to type 'pair<basic_string<...>, [...]>' 
        cannot bind to a value of unrelated type 'pair<const basic_string<...>, [...]>'
        */
        // get_pair3(ipair);
        get_pair4(ipair);
    }
    return 0;
}
/*
int auto_calibrate_intensity_thr(std::pair<std::string,std::vector<sensor_msgs::LaserScan> > &scans)
std::map<std::string,std::vector<sensor_msgs::LaserScan> > scansmap;
for(std::pair<std::string,std::vector<sensor_msgs::LaserScan> > iscans&:scansmap){   // 如果是引用，则编译报错
// for(auto iscans:scansmap){
    result[iscans.first] = auto_calibrate_intensity_thr(iscans);
如果是引用，则编译报错用右值初始化左值引用！
error: invalid initialization of non-const reference of type ‘std::pair<std::__cxx11::basic_string<char>, 
        std::vector<sensor_msgs::LaserScan_<std::allocator<void> > > >&’ from an rvalue of type 
        ‘std::pair<std::__cxx11::basic_string<char>, std::vector<sensor_msgs::LaserScan_<std::allocator<void> > > >’
        for(std::pair<std::string,std::vector<sensor_msgs::LaserScan> > &iscans:scansmap){   // &
                                                                                ^


*/