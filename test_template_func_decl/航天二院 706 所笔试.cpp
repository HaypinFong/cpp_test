// #include<bits/stdc++.h>
#include<map>
#include <iostream>
#include<string>
using namespace std;
int main() {
    int n, m;
	cin>>n>>m;
    map<int, bool> record;
    int a[n];
    for(int i = 0;i<n;i++)
    {    
        cin>>a[i];
        record.insert(std::make_pair(a[i],true));
    }
    //for(int i = 0;i<n;i++)
    //    cout<<a[i]<<' ';
    int num;
    while (cin >> num) {
        if (record.find(num) != record.end())
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}
int temp() {
    int n, m;
	cin>>n>>m;
    map<int, bool> record;
    string str;
    //str = "hahha";
    //cout<<str.substr(1,3)<<endl;
    cin >> str;
    cout<<str<<endl;
    int i = 0;
    while (str[i] == ' ' && i < str.size())
        i++;
    int j = i;
    while (j < str.size()) {
        while (str[j] != ' ' && j < str.size())
            j++;
        string numStr = str.substr(i, j - i);
        record.insert(std::make_pair(std::stoi(numStr), true));
        while (str[j] == ' ' && j < str.size())
            j++;
        i = j;
    }
    int num;
    while (cin >> num) {
        if (record.find(num) != record.end())
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}

