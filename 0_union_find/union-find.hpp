#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_
#include <iostream>
#include <vector>
using namespace std;

//���鼯 �����νṹ��	ע������ֻ��ѧϰ���ݽṹ��Ŀ�ģ���û������ϸ�µ��쳣��� 
class UnionFind{
private:
	vector<int> root;
	vector<int> size;	//��С�����鵽������� 
public:
	UnionFind(int num);
	int find(int k);	//�õ��� 
	void Union(int m, int n);	//�ϲ����ߵĸ��ڵ� 
	bool connected(int m, int n);	//��������Ƿ���ͨ 
public: 
	void print();	//��ӡ������Ϣ 
}; 

#include "union-find_impl.hpp"

#endif 
