#include <iostream>
#include <string>
#include <regex>
#include <vector>
using namespace std;
int main ()
{
  std::string s ("this subject has a submarine as a subsequence");
  std::smatch m;
  std::regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

  std::cout << "Target sequence: " << s << std::endl;
  std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
  std::cout << "The following matches and submatches were found:" << std::endl;

  while (std::regex_search (s,m,e)) {
    cout<<m.empty()<<" "<<m.size()<<" "<<m.position()<<" ";
    cout<<m.str()<<" "<<m.ready()<<endl;
    for(size_t i(0);i<m.size();i++)
        cout<<m[i]<<" ";    // m[0]是搜索到的目标子串，m[1:n]是捕获组
    cout<<endl;
    cout<<m.prefix().str()<<"|"<<m.suffix().str()<<endl;    // 搜索到的目标子串之前、之后的部分
    // for (auto x:m) std::cout << x << " ";
    std::cout <<"__"<< std::endl;
    s = m.suffix().str();
  }
  string rmflag("chaos -fidIRrvWxP chaos");
  regex rmrgx("-[fidIRrvWxP]*");
  if(std::regex_search(rmflag,m,rmrgx)){
    cout<<m.str()<<endl;
    cout<<m.prefix().str()<<"|"<<m.suffix().str()<<endl;
  }
  
  regex rgx(" ");
  string saying("/root/path/a long name.docx");
  smatch res;
  string saying_(""),endstr("");
  while(regex_search(saying,res,rgx)){
      saying_ += res.prefix().str()+(std::string)"\\ ";
      saying = res.suffix().str();
  }
  saying_ += saying;
  cout<<saying_<<endl;
  cout<<saying<<endl;



  std::string s2 ("there is a subsequence sub in the string\n");
  std::regex e2 ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

  // using string/c-string (3) version:
  std::cout << std::regex_replace (s2,e2,"sub-$2");

  // using range/c-string (6) version:
  std::string result;
  std::regex_replace (std::back_inserter(result), s2.begin(), s2.end(), e2, "$2");
  std::cout << result;

  // with flags:
  std::cout << std::regex_replace (s2,e2,"$1 and $2",std::regex_constants::format_no_copy);
  std::cout << std::endl;

  string str("测试\ 空格 .docx"),str_repl("");
  regex rgx2(" ");
  regex_replace(std::back_inserter(str_repl),str.begin(),str.end(),rgx2,"\\ ");
  cout<<str_repl<<endl;

  size_t idx(str.find_last_of("."));
  cout<<"file name no suffix: "<<str.substr(0,idx)<<endl;
  cout<<"file suffix: "<<str.substr(idx)<<endl;


  str = ".docx\\ \\ ";
  while(str.substr(str.size()-1)==(std::string)" "){
      str = str.substr(0,str.size()-1);
      cout<<str<<"_"<<str.size()<<endl;
  }
  cout<<str<<"_"<<str.size()<<endl;

  str = "内建模板标签和过滤器Built-in template tags and filters.docx";
  regex rgx3("[[:space:]]*-([dfPRrvW]*)i");  // 重复的是紧前正则表达式，也包含"重复紧前匹配内容"的意思
  smatch res3;
  if(regex_search(str,res3,rgx3)){
      cout<<res3.prefix().str()<<" and "<<res3.suffix().str()<<endl;
      cout<<res3[0]<<endl;  // -bifP
      cout<<res3[1]<<endl;  // bif
  }

  str = "node.";
  regex dot("\\.");
  cout<<"find \\. "<<regex_search(str,dot)<<endl;
  size_t suffix_idx( str.find_last_of(".") );
  cout<<suffix_idx<<endl;

  vector<int> arr{1,2,3},arr2;
  arr2.assign(arr.end()-3,arr.end());
  for(int &i:arr2)
      cout<<i<<" ";
  cout<<endl;
  return 0;
}