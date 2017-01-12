#ifndef _BINOMIAL_HEAP_H_
#define _BINOMIAL_HEAP_H_
#include <iostream>
#include <vector>
using namespace std;

/**
 *	������С� //ʹ����Weiss��˼·�Լ��㷨��ʾ��������ȫ��ͬ��δ�����ġ�  ��Ҫ�ĵط�����ע�͡� 
 *
 */
template <typename T, typename Comp = std::less<T>>
class BinomialHeap{
public:
	struct TreeNode{
		T data;
		TreeNode* leftChild;
		TreeNode* nextSibling;	//���� ����-�ֵ� ��ʾ��
		
		TreeNode(T data, TreeNode* leftChild = nullptr, TreeNode* nextSibling = nullptr): 
											data(data), leftChild(leftChild), nextSibling(nextSibling){}; 
	};
private:
	vector<TreeNode*> forest;	//forest��ÿһ��slot�ֱ𱣴�2^0 2^1 2^2 2^3......����������
	Comp comp;
	int currentSize = 0; 	//�ܵĽ������������v[0],v[2],v[3]�Ѿ��洢����currentSize = 2^0+2^2+2^3 = 1<<0 + 1<<2 + 1<<3.
private:
	TreeNode* combineTrees(TreeNode* t1, TreeNode* t2);	//ע�⣡������� ͬ�����������ĺϲ�����2^2��2^2�ϲ����֣� 
	void merge(BinomialHeap & rhs);
	int findMinIndex();
	int capacity();
public:
	BinomialHeap() = default;
	BinomialHeap(T const & x);
public:
	bool isEmpty();
	void insert(T const & x);
	T getMin();
	void deleteMin();
};



#endif 
