#ifndef _LLRBTREE_H_
#define _LLRBTREE_H_
#include <iostream>
using namespace std;

//SedgeWick左倾红黑树LLRB。 		//delete方法尚未弄清楚。。故而没有实现 
template <typename T, typename Comp = std::less<T>>
class RedBlackTree{
private:
	enum{RED, BLACK};
	struct TreeNode{
		T data;
		TreeNode* left;
		TreeNode* right;
		int size;
		int color;
		
		TreeNode(T data, TreeNode* left = nullptr, TreeNode* right = nullptr): data(data), left(left), right(right), size(1), color(RED){}; 
	};
private:
	Comp comp;
	TreeNode* root = nullptr;
private:
	void insert(TreeNode* & x, const T & data);
	// void remove(TreeNode* & x, const T & data);
	void balance(TreeNode* &x);
	void rotateLeft(TreeNode* &x);
	void rotateRight(TreeNode* &x);
	void flipColors(TreeNode* &x);
	bool isRed(TreeNode* x);
	int size(TreeNode* x);
public:
	RedBlackTree() = default;
	void insert(const T & data){insert(root, data); root->color = BLACK;}	//千万别忘了把根节点变成BLACK！！！ 
	void remove(const T & data){remove(root, data);}
	void inOrderTraversal();
};


#endif 
