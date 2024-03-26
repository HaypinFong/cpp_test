#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include"yaml-cpp/yaml.h"
#include"yaml-cpp/exceptions.h"
using namespace std;
void read_yaml(std::string fname){
    try{
        fname = "Node_extra_param.yaml";
        YAML::Node fnode = YAML::LoadFile(fname);
        // cout<<fnode["params/param1"]<<endl;
        std::string str("peter_chargingpile_identification/intensity_thrs/front_laser");
        cout<<fnode[str]<<endl;
        if(!fnode[str])
            cout<<"does exist "<<str<<" : "<<fnode[str]<<endl;
        
        cout<<fnode["intensity_thrs"]["front_laser"].as<int>()<<endl;
        cout<<typeid(fnode["intensity_thrs"]).name()<<endl;                 // N4YAML4NodeE
        YAML::Node node1( fnode["intensity_thrs"] );
        cout<<node1["front_laser"].as<int>()<<endl;
        cout<<typeid(fnode["intensity_thrs"]["front_laser"]).name()<<endl;  // N4YAML4NodeE
        // cout<<( decltype(fnode["intensity_thrs"])==YAML::NodeType::Map )<<endl;
        fnode["intensity_thrs"]["front_laser"] = 99;
        std::ofstream fout(fname.c_str());
        fout<<fnode;

        // YAML::Node 
    }catch(std::exception& e){
        cout<<e.what()<<endl;
    }catch(YAML::BadFile& e){
        cout<<e.what()<<endl;
    }
}
bool write_yaml(std::string fname){
    try{
        YAML::Node fnode = YAML::LoadFile(fname);
        fnode["intensity_thr"] = 150;
        std::ofstream fout(fname.c_str());
        fout<<fnode;
        return true;
    }catch(YAML::BadFile &e){
        cout<<e.what()<<endl;
        cout<<"yaml file donot exit ,will create it"<<endl;

        YAML::Node fnode;
        fnode["intensity_thr"] = 150;
        std::ofstream fout(fname.c_str());
        fout<<fnode;
        return true;
    }catch(std::exception &e){
        cout<<e.what()<<endl;
        
        // YAML::Node fnode;
        // fnode["intensity_thr"] = 150;
        // std::ofstream fout(fname.c_str());
        // fout<<fnode;
        // return true;
    }
    return false;
}
bool write_yaml(std::string fname,std::vector<std::string> &name_list){     // 左值引用
    try{
        YAML::Node fnode = YAML::LoadFile(fname);
        YAML::Node *pnode_pre(&fnode);      // 错误，YAML::Node的基本类型标量、列表、字典，引用，不是类似XML的嵌套节点！
        for(size_t i(0);i<name_list.size()-1;i++){
            YAML::Node nodet;
            (*pnode_pre)[name_list[i]] = nodet; // 赋值操作是指针赋值，并不是YAML::Node对象拷贝
            /*
            error: taking the address of a temporary object of 
            type 'YAML::Node' [-Waddress-of-temporary]
            */
            // pnode_pre = &(*pnode_pre)[name_list[i]];
        }
        (*pnode_pre)[*(name_list.end()--)] = 130;

        std::ofstream fout(fname.c_str());
        fout<<fnode;
        return true;
    }catch(YAML::BadFile &e){
        cout<<e.what()<<endl;
        cout<<"yaml file donot exit ,will create it"<<endl;

        YAML::Node fnode;
        YAML::Node *pnode_pre(&fnode);
        for(size_t i(0);i<name_list.size()-1;i++){
            YAML::Node nodet;
            (*pnode_pre)[name_list[i]] = nodet;
            // pnode_pre = &(*pnode_pre)[name_list[i]];
        }
        (*pnode_pre)[*(name_list.end()--)] = 130;

        std::ofstream fout(fname.c_str());
        fout<<fnode;
        return true;
    }catch(std::exception &e){
        cout<<e.what()<<endl;
        
        // YAML::Node fnode;
        // fnode["intensity_thr"] = 150;
        // std::ofstream fout(fname.c_str());
        // fout<<fnode;
        // return true;
    }
    return false;
}
bool write_yaml(std::string fname,std::vector<std::string> &&name_list){        // 右值引用
    try{
        YAML::Node fnode = YAML::LoadFile(fname);
        std::vector<YAML::Node*> arr;
        YAML::Node *pnode_tail(new YAML::Node(YAML::NodeType::Scalar));
        arr.push_back(pnode_tail);
        (*pnode_tail)[*(name_list.end()--)] = 150;
        YAML::Node *pnode_pre(nullptr),*pnode_next(pnode_tail);
        for(int i(name_list.size()-2);i>0;i--){     // 错误，YAML::Node的基本类型标量、列表、字典，引用，不是类似XML的嵌套节点！
            pnode_pre = new YAML::Node();
            arr.push_back(pnode_pre);
            (*pnode_pre)[name_list[i]] = *pnode_next;
            pnode_next = pnode_pre;
        }
        fnode[name_list[0]] = *pnode_pre;
        std::ofstream fout(fname.c_str());
        fout<<fnode;

        for(YAML::Node *pnode:arr)
            delete pnode;
        return true;
    }catch(YAML::BadFile &e){
        cout<<e.what()<<endl;
        cout<<"yaml file donot exit ,will create it"<<endl;

        YAML::Node fnode;
        std::vector<YAML::Node*> arr;
        YAML::Node *pnode_tail(new YAML::Node(YAML::NodeType::Scalar));
        arr.push_back(pnode_tail);
        (*pnode_tail)[*(name_list.end()--)] = 150;
        YAML::Node *pnode_pre(nullptr),*pnode_next(pnode_tail);
        for(int i(name_list.size()-2);i>0;i--){
            pnode_pre = new YAML::Node();
            arr.push_back(pnode_pre);
            (*pnode_pre)[name_list[i]] = *pnode_next;
            pnode_next = pnode_pre;
        }
        fnode[name_list[0]] = *pnode_pre;
        std::ofstream fout(fname.c_str());
        fout<<fnode;

        for(YAML::Node *pnode:arr)
            delete pnode;
        return true;
    }catch(std::exception &e){
        cout<<e.what()<<endl;
        
        // YAML::Node fnode;
        // fnode["intensity_thr"] = 150;
        // std::ofstream fout(fname.c_str());
        // fout<<fnode;
        // return true;
    }
    return false;
}

bool write_yaml_map(std::string fname,std::map<std::string,std::string> mymap){
    try{
        // 如果yaml文件不存在就创建一个
        ifstream file(fname.c_str());
        if(!file.good()){
            ofstream File;
            File.open(fname.c_str(),ios::out|ios::trunc);
            File.close();
            cout<<fname.c_str()<<" not exist, will create it now"<<endl;
        }
        YAML::Node fnode = YAML::LoadFile(fname);
        fnode["mymap"] = "just_mymap";
        std::ofstream fout(fname.c_str());
        fout << fnode;
        fout.close();
        cout<<"update done"<<endl;
        return true;
    }catch(YAML::BadFile &e){
        cout<<"YAML::BadFile "<<e.what()<<endl;
        // YAML::Emitter out;
        // out << mymap;        // 格式错误

        // YAML::Node node;
        // node["key"] = "val"; // 格式错误

        // std::string str("{");
        // str += "key";
        // str += ", ";
        // str += "val";
        // str += "}}";
        // YAML::Node node( YAML::Load(str.c_str() ) );

        // YAML::Node node( YAML::Load("{key: val}"));

        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "key";
        out << YAML::Value << "val";
        out << YAML::EndMap;
        assert(out.good());
        if(out.GetLastError().size()>0)
            cout<<"Emitter error: "<<out.GetLastError()<<endl;

        
        std::ofstream fout(fname.c_str());
        // fout << node;
        fout << out.c_str();
        fout.close();
        cout<<"create done"<<endl;
        return true;
    }catch(std::exception &e){
        cout<<e.what()<<endl;
    }
    return false;
}

int main(int argc, char **argv){
    cout<<"start"<<endl;
    read_yaml("mydict.yaml");
    YAML::Emitter out;
    out << "Hello, World!";
    std::cout << "Here's the output YAML:" << out.c_str()<<endl; // prints "Hello, World!"

    // write_yaml("mydict2.yaml");
    // write_yaml("mydict3.yaml",std::vector<std::string>{"parent","son","grandson"});
    write_yaml_map("mydict3.yaml",
        std::map<std::string,std::string>{
        {"parent","bao"},{"son","long"},{"granddau","luo"}}
        );
    write_yaml_map("mydict3.yaml",
        std::map<std::string,std::string>{
        {"parent","bao"},{"son","long"},{"granddau","luo"}}
        );
    return 0;
}