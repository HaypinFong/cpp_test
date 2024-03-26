#include <iostream>
#include <set>
using namespace std;

//定义点类 
class Point{
public:
	int x,y;
	Point(int _x = 0,int _y = 0){
		x = _x;
		y = _y;
	}
        
    friend ostream & operator << (ostream & o,const Point & A){
    	o << "x = " << A.x << "  ,y = " << A.y << endl;
    	return o;
	}
};


//定义排序规则 
class cmp											//定义排序类
{
	public:											//须在公有方法内定义
        bool operator () ( Point  A,  Point  B) 	//重载（）符号
        {
               if(A.x != B.x){
                	return A.x < B.x; 				//x小的放前面
				}
				else{
					return A.y < B.y;				//x相同则y小的放前面
				}
        }
};
int main() {
	
	//创建集合并添加新元素 
	multiset<Point,cmp> A;
	A.insert(Point(1,1));
	A.insert(Point(1,1));
	A.insert(Point(2,2));
	A.insert(Point(2,4));
	A.insert(Point(4,2));
	A.insert(Point(4,4));	
	
	//输出
	cout << "A.size() = " << A.size() << endl;
	cout << "A.empty() = " << A.empty() << endl;
	
	//输出multiset全部元素 
	cout << "set中的全部元素为: " << endl; 
	for(set<Point>::iterator it = A.begin();it!=A.end();it++){
		cout << *it << " ";
	}
	cout << endl;
	
	//删除一个元素 
	A.erase(Point(1,1));
	cout << "删除一个元素后set中的全部元素为: " << endl ; 
	for(set<Point>::iterator it = A.begin();it!=A.end();it++){
		cout << *it << " ";
	}
	cout << endl;
	
	//清空multiset 
	A.clear();
	cout << "清空set后的全部元素为: " << endl; 
	for(set<Point>::iterator it = A.begin();it!=A.end();it++){
		cout << *it << " ";
	}
	cout << endl;	
	
	return 0;
}
