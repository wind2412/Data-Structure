#ifndef _BST_H_
#define _BST_H_
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

//������������ ʹ����ȫ�������ǵݹ飡
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
	BST(TreeNode * root = nullptr) :root(root) {};	//����put���졣
	void preOrderTraversal1();
	void preOrderTraversal2();
	void inOrderTraversal();
	void postOrderTraversal();
	void levelOrderTraversal();
	void put(T data);
	int getHeight();
	int getMin();
	void deleteMin();	//deleteMinԭ���ҵ��趨�Ƿ���getMin��ͬ��ֵ������ɾ������С����ֵ������������getMinЧ���ظ��ˡ����ұ���Ҫ���¸��ڵ�!!
	void deleteNode(T data);
	~BST();
};

//#include "BST.cpp"

#endif
