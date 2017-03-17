#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_
#include <iostream>
#include <vector>
using namespace std;

//并查集 （树形结构）	注：本着只是学习数据结构的目的，并没做过于细致的异常检查 
class UnionFind{
private:
	vector<int> root;
	vector<int> size;	//把小的树归到大的树中 
public:
	UnionFind(int num);
	int find(int k);	//得到根 
	void Union(int m, int n);	//合并两者的根节点 
	bool connected(int m, int n);	//检测两者是否连通 
public: 
	void print();	//打印调试信息 
}; 

#include "union-find_impl.hpp"

#endif 
