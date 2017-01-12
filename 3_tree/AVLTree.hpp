#ifndef _AVLTree_H_
#define _AVLTree_H_
#include <stack>
using namespace std;

//AVLTree����ת��root�������ӽڵ��ǽ�����ת�� 
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
	//����ָ�����ã�ȫ�ֲ�����1.����ֱ�����ϱ�ԭֵnew����nullҲû�£���Ϊ���ǿ�����	//2.ע��ݹ鲻Ҫ�ٴ������x��Ҫ���ݹ����֮��x���Ѿ���ֵ�ˡ� 
	void insert(AVLNode<T>* &x, const T & data);	 
	void balance(AVLNode<T>* &x);
	void leftRotation(AVLNode<T>* &x);	//���ڵ����׸ı�ģ�����rotation��insert��remove�ȣ�ֱ�ӰѸ��ڵ�����壨���ã�����ȥ���ˡ�����Java��ҪŪ���������ˡ� 
	void rightRotation(AVLNode<T>* &x);
	void leftRightRotation(AVLNode<T>* &x);
	void rightLeftRotation(AVLNode<T>* &x);
	void remove(AVLNode<T>* &x, const T & data);	//xӦ����root������Ҳ�п���move root��ע���������remove������remove�����ǰ�Ҫ���滻��ֵ����Ҫ��ɾ���ĵ㡣 
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
