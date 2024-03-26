/*
给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
示例 1:

输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

方法一：滑动窗口
思路和算法

我们先用一个例子考虑如何在较优的时间复杂度内通过本题。

我们不妨以示例一中的字符串 {abcabcbb}abcabcbb 为例，找出从每一个字符开始的，
不包含重复字符的最长子串，那么其中最长的那个字符串即为答案。对于示例一中的字符串，我们列举出这些结果，其中括号中表示选中的字符以及最长的字符串：

以 {(a)bcabcbb}(a)bcabcbb 开始的最长字符串为 {(abc)abcbb}(abc)abcbb；
以 {a(b)cabcbb}a(b)cabcbb 开始的最长字符串为 {a(bca)bcbb}a(bca)bcbb；
以 {ab(c)abcbb}ab(c)abcbb 开始的最长字符串为 {ab(cab)cbb}ab(cab)cbb；
以 {abc(a)bcbb}abc(a)bcbb 开始的最长字符串为 {abc(abc)bb}abc(abc)bb；
以 {abca(b)cbb}abca(b)cbb 开始的最长字符串为 {abca(bc)bb}abca(bc)bb；
以 {abcab(c)bb}abcab(c)bb 开始的最长字符串为 {abcab(cb)b}abcab(cb)b；
以 {abcabc(b)b}abcabc(b)b 开始的最长字符串为 {abcabc(b)b}abcabc(b)b；
以 {abcabcb(b)}abcabcb(b) 开始的最长字符串为 {abcabcb(b)}abcabcb(b)。
发现了什么？如果我们依次递增地枚举子串的起始位置，那么子串的结束位置也是递增的！这里的原因在于，
假设我们选择字符串中的第 k 个字符作为起始位置，并且得到了不包含重复字符的最长子串的结束位置为r_kr
。那么当我们选择第 k+1个字符作为起始位置时，首先从 k+1到r_k的字符显然是不重复的，
并且由于少了原本的第k个字符，我们可以尝试继续增大r_k，直到右侧出现了重复字符为止。
*/
#include<iostream>
#include<string>
#include<unordered_set>
using namespace std;
int longest_norepeated_character_substr(string str){
    int maxlen(1);
    unordered_set<char> sets;
    sets.insert(str[0]);
    for(size_t istart(0),iend(0);istart<str.size()-1;istart++)
    {
        while(iend+1<str.size() && sets.count(str[iend+1])<=0)  // test str[iend+1]
            sets.insert(str[++iend]);
        if(iend-istart+1>maxlen)
            maxlen=iend-istart+1;
        sets.erase(str[istart]);
    }
    return maxlen;
}
int main(int argc,char *argv[]){
    cout<<longest_norepeated_character_substr((string)"abcabcbb")<<endl;
    cout<<longest_norepeated_character_substr((string)"bbbbb")<<endl;
    cout<<longest_norepeated_character_substr((string)"pwwkew")<<endl;
}
