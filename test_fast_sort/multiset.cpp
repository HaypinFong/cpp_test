#include<iostream>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;
struct Student {
    char name[20];
    int id;
    int score;
};
Student students[] = { {"Jake",110,79},{"Make",112,66},{"Ala",108,88},
    {"Zero",101,78},{"Cindy",128,99} };
struct Rule {
    bool operator()(const Student& s1, const Student& s2)const {
        if (s1.score != s2.score)
            return s1.score > s2.score;
        else
            return (strcmp(s1.name, s2.name) < 0);
    }
};
int main() {
    multiset<Student, Rule>st;
    for (int i = 0; i < 5; i++)
        st.insert(students[i]);
    multiset<Student, Rule>::iterator p;
    for (p = st.begin(); p != st.end(); ++p){
        cout << p->name << "  " << p->id << "  " << p->score << endl;
    }
    Student s = { "Mary",111,89 };
    p = st.find(s);
    if (p != st.end())
        cout << p->name << "  " << p->id << "  " << p->score << endl;
    else cout << "not found" << endl;
    return 0;
}