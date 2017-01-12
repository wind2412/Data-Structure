#ifndef _BST_H_
#define _BST_H_
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

//二叉搜索树。 使用完全迭代，非递归！
template <typename T, typename Comp = std::less<T>>
class BST {
public:
	struct TreeNode {
		public:
			T data;
			TreeNode* left;
			TreeNode* right;
		public:
			TreeNode(T data, TreeNode* left = nullptr, TreeNode* right = nullptr) :data(data), left(left), right(right) {};
	};
public:
	TreeNode* root;	
	Comp comp;
private:
	void makeEmpty();
	void makeEmpty() const;
public:
	BST(TreeNode * root = nullptr) :root(root) {};	//不断put构造。
	void preOrderTraversal1();
	void preOrderTraversal2();
	void inOrderTraversal();
	void postOrderTraversal();
	void levelOrderTraversal();
	void put(T data);
	int getHeight();
	int getMin();
	void deleteMin();	//deleteMin原先我的设定是返回getMin相同的值，即被删除的最小结点的值，但是这样与getMin效果重复了。而且必须要更新根节点!!
	void deleteNode(T data);
	~BST();
};

//#include "BST.cpp"

#endif
