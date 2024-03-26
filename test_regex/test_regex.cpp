// https://www.cplusplus.com/reference/regex/regex_search/
// regex_search example
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
using namespace std;
#define flag regex_constants::ECMAScript
int main ()
{
  string s ("this subject has a submarine as a subsequence &sub_ #sub _");
  smatch m;
  regex e ("\\b(sub)([^ ]*)",flag);   // matches words beginning by "sub"，
                // sub后面紧跟一个非空格字符但允许重复零次，即对sub后面紧跟字符无要求
  regex e2 ("\\b(sub)([^ ]+)",flag);  // 要求sub后面紧跟一个非空格字符且必须有，最后的"#sub _"就不匹配
  regex e1("\\bsub\\b",flag);    // 单独的\表示对其后字符转义，比如\n，连续的\\表示单个\，只有最后的"#sub _"匹配
  cout<<"\b"<<endl;     // \b表示回删，是文件格式转义，
  cout<<"\\b"<<endl;    // "\b"，\\b表示字符\加一个字符b，表示词边界，&sub #sub也算词边界，因为不是字母分割

  cout << "Target sequence: " << s << endl;
  cout << "Regular expression: /\\b(sub)([^ ]*)/" << endl;
  cout << "The following matches and submatches were found:" << endl;
  cout << regex_search(s,e)<<endl;
  while (regex_search (s,m,e1)) {
    for (auto x:m) cout << x << " ";
    cout << endl;
    s = m.suffix().str();
  }

  cout<<"---------"<<endl;
  string str("60-90");
  // regex reg("([0-9]+)-([0-9]+)");
  // regex reg("([[:digit:]]+)-([[:digit:]]+)");
  // regex reg("([[:d:]]+)-([[:d:]]+)");
  regex reg("(\\d+)-(\\d+)");
  if(regex_match(str,m,reg)){
    cout<<m.size()<<endl;
    for(auto i:m){
      cout<<i.str()<<' ';
    }
    cout<<endl;
    auto isub(m.begin());
    for(isub++;isub!=m.end();isub++){
      cout<<isub->str()<<' ';
    }
    cout<<endl;
  }

  cout<<"<<<<<<"<<endl;
  string strcn("蒲");
  regex regcn("\u84b2");
  if(regex_match(strcn,m,regcn)){
    cout<<m.size()<<endl;
    for(auto i:m){
      cout<<i.str()<<' ';
    }
    cout<<endl;
  }
  // map<const string,vector<float> >::iterator ite;   // (nullptr)
  // if(ite)
  //   cout<<"do exist ite"<<endl;
  // else
  //   cout<<"do not exist ite"<<endl;

  return 0;
}