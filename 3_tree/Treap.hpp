#ifndef _TREAP_H_
#define _TREAP_H_
#include <iostream>
using namespace std;

/**
 *  http://blog.csdn.net/u014634338/article/details/49612159
 *	Treap = Tree + Heap�� Treap�����������������������ʣ����Դ���priority���ȼ�����ѵ����ʡ� 
 *	Treapֻ��������ת��ʽ����תʱ��һ�����ڲ�������ƻ���priority�Ķ����ʡ�����rotate���ı�����������ʵ�inOrderTraversal,��˿���
 *	��˵�������priority��˳�� 
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
	void balance(TreeNode* &x);	//��Ҫʵ��balance���� �������鷳�ˣ�����Ϊ���ұ߲���һ���Ҫ������parent������������߲��������ǹ̶��ģ���Ҫ��һ���������3����д�� 
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
