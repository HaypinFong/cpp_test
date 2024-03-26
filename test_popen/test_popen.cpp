#include<iostream>
#include"stdio.h"
#include"string.h"
#include<string>
#include<map>
#include<vector>
using namespace std;
int main()
{
    FILE *fp = NULL;
    char cmd[1024];
    char buf[1024];
    char result[4096];
    sprintf(cmd, "%s","ls -a|grep CMake");
    if( (fp = popen(cmd, "r")) != NULL)
    {
        while(fgets(buf, 1024, fp) != NULL)
        {
            strcat(result, buf);
        }
        pclose(fp);
        fp = NULL;
    }
    cout<<"result: "<<result<<endl;

    string restr("haha /hie/eoghnaoeign/");
    int iblack = restr.find_last_of(' ');
    string path(restr.begin()+iblack+1,restr.end());
    path.append("_&");
    cout<<"path: "<<path<<endl;

    map<string,string> s2s;
    s2s["aloha"]="halo";
    cout<<s2s["aloha"]<<endl;

    map<string,string> mapstr{{"aloha","hello"},{"amigo","idiots"}};   // map初始化列表
    cout<<mapstr["aloha"]<<endl;
    cout<<mapstr["amigo"]<<endl;

    pair<string,string> pss{"pa","pair"}; // pair初始化列表
    cout<<pss.first<<endl;

    // vector初始化列表，pair初始化列表
    vector<pair<string,string> >vpair{{"aloha","hello"},{"amigo","idiots"}}; 
    cout<<vpair[1].second<<endl;

    vector<string> vstr{"aloha","halo"};    // vector初始化列表
    cout<<vstr[1]<<endl;

    char arr[]={'a','l','o','h','a','\0'};  // 数组初始化列表
    cout<<arr[1]<<endl;
    return 0;
}