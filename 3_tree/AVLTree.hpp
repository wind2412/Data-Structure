#ifndef _AVLTree_H_
#define _AVLTree_H_
#include <stack>
using namespace std;

//AVLTree的旋转是root结点控制子节点们进行旋转。 
template <typename T>
class AVLNode{
public:
	T data;
	AVLNode* left;
	AVLNode* right;
	int height = 1;
	
public: 
	AVLNode(const T & data, AVLNode* left, AVLNode* right):data(data), left(left), right(right){};
};

template <typename T>
class AVLTree{
private:
	AVLNode<T>* root; 

private:
	//传递指针引用：全局参数。1.可以直接在上边原值new，是null也没事，因为不是拷贝。	//2.注意递归不要再传递这个x。要不递归回来之后，x就已经变值了。 
	void insert(AVLNode<T>* &x, const T & data);	 
	void balance(AVLNode<T>* &x);
	void leftRotation(AVLNode<T>* &x);	//根节点容易改变的，像是rotation，insert，remove等，直接把根节点的正体（引用）传进去好了。不用Java还要弄两个函数了。 
	void rightRotation(AVLNode<T>* &x);
	void leftRightRotation(AVLNode<T>* &x);
	void rightLeftRotation(AVLNode<T>* &x);
	void remove(AVLNode<T>* &x, const T & data);	//x应该是root。但是也有可能move root。注意二叉树的remove不是真remove，而是把要被替换的值覆盖要被删除的点。 
	int height(AVLNode<T>* x) const; 
	void inOrderTraversal(AVLNode<T>* x);
	
public:
	AVLTree() = default;
	void insert(const T & data){insert(root, data);}
	void remove(const T & data){remove(root, data);}
	void inOrderTraversal();
}; 

template <typename T>
void AVLTree<T>::inOrderTraversal(){
	inOrderTraversal(root);
}
#endif
