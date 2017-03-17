#ifndef _TREAP_H_
#define _TREAP_H_
#include <iostream>
using namespace std;

/**
 *  http://blog.csdn.net/u014634338/article/details/49612159
 *	Treap = Tree + Heap。 Treap树自身结点满足二叉查找树性质，而自带的priority优先级满足堆的性质。 
 *	Treap只有两种旋转方式。旋转时候一定由于插入过程破坏了priority的堆性质。由于rotate不改变二叉搜索性质的inOrderTraversal,因此可以
 *	借此调整满足priority堆顺序。 
 */
template <typename T, typename Comp = std::less<T>>
class Treap{
private:
	struct TreeNode{
		T data;
		int priority;
		TreeNode* left;
		TreeNode* right;
		int size;
		
		TreeNode(T data, int priority, TreeNode* left = nullptr, TreeNode* right = nullptr):
			data(data), priority(priority), left(left), right(right), size(1){}
	};
private:
	Comp comp;
	TreeNode* root = nullptr;
private:
	void insert(TreeNode* &x, T data, int priority);
	void remove(TreeNode* &x, T data);
	void rotateWithLeftChild(TreeNode* &x);
	void rotateWithRightChild(TreeNode* &x);
	void balance(TreeNode* &x);	//不要实现balance！！ 反倒更麻烦了！！因为在右边插入一般就要对它的parent进行左旋，左边插右旋，是固定的！不要在一个函数里边3个都写！ 
	int size(TreeNode* &x);
	int priority(TreeNode* &x); 
public:
	Treap() = default; 
	~Treap();
public:
	void insert(T data, int priority){insert(root, data, priority);};
	void remove(T data){remove(root, data);};
	void inOrderTraversal();
};



#endif
