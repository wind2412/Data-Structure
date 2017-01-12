#ifndef _BINOMIAL_HEAP_H_
#define _BINOMIAL_HEAP_H_
#include <iostream>
#include <vector>
using namespace std;

/**
 *	二项队列。 //使用了Weiss的思路以及算法表示。代码完全相同，未做更改。  必要的地方做了注释。 
 *
 */
template <typename T, typename Comp = std::less<T>>
class BinomialHeap{
public:
	struct TreeNode{
		T data;
		TreeNode* leftChild;
		TreeNode* nextSibling;	//采用 儿子-兄弟 表示法
		
		TreeNode(T data, TreeNode* leftChild = nullptr, TreeNode* nextSibling = nullptr): 
											data(data), leftChild(leftChild), nextSibling(nextSibling){}; 
	};
private:
	vector<TreeNode*> forest;	//forest的每一个slot分别保存2^0 2^1 2^2 2^3......个结点的树。
	Comp comp;
	int currentSize = 0; 	//总的结点个数。即如果v[0],v[2],v[3]已经存储，则currentSize = 2^0+2^2+2^3 = 1<<0 + 1<<2 + 1<<3.
private:
	TreeNode* combineTrees(TreeNode* t1, TreeNode* t2);	//注意！！这个是 同【次数】树的合并！！2^2和2^2合并这种！ 
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
