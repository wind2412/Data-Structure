#ifndef _RBTREE_IMPL_H_
#define _RBTREE_IMPL_H_
#include "LLRBTree.hpp"
#include <stack>

template <typename T, typename Comp>
using TreeNode = typename RedBlackTree<T, Comp>::TreeNode;

/*****************��������*******************/ 
template <typename T, typename Comp>
int RedBlackTree<T, Comp>::size(TreeNode* x){
	return x == nullptr ? 0 : x->size;
}

template <typename T, typename Comp>
bool RedBlackTree<T, Comp>::isRed(TreeNode* x){	//nullptr��㵱�ɺ�ɫ������µ�ȫ�Ǻ�ɫ�����ˣ� 
	if(x == nullptr)	return false;
	return x->color == RED;
}

/*****************��Ҫ����*******************/
template <typename T, typename Comp>	//����������������Ӧ�ö��ǣ������ڵ�֮����߶���RED�� 
void RedBlackTree<T, Comp>::rotateLeft(TreeNode* &x){	//������������x->right->color == RED. 
	TreeNode* temp = x->right;
	x->right = temp->left;
	temp->left = x;
	temp->color = x->color;
	x->color = RED;
	x->size = temp->size;
	temp->size = size(temp->left) + size(temp->right) + 1;
	x = temp;	//ע��ǧ��Ҫ����䣡�������ڵ�~�� 
	return;
}

template <typename T, typename Comp>
void RedBlackTree<T, Comp>::rotateRight(TreeNode* &x){	//�������������û��ʹ��ֱ�������ģ��˺�����Ϊ��ĺ����Ļ�����//�����ľ��� 
	TreeNode* temp = x->left;
	x->left = temp->right;
	temp->right = x;
	temp->color = x->color;
	x->color = RED;
	x->size = temp->size;
	temp->size = size(temp->left) + size(temp->right) + 1;
	x = temp; 
	return;
}

template <typename T, typename Comp>
void RedBlackTree<T, Comp>::flipColors(TreeNode* &x){
	x->color = !x->color;
	x->left->color = !x->left->color;
	x->right->color = !x->right->color;
}

template <typename T, typename Comp>
void RedBlackTree<T, Comp>::balance(TreeNode* &x){
	if(x == nullptr)	return;
	if(!isRed(x->left) && isRed(x->right))	rotateLeft(x);
	if(isRed(x->left) && isRed(x->left->left))	rotateRight(x);	//���Ư����x->left->left�����Ŀ����ԣ���x->left==nullptr���Ŀ�������isRed(x->left)�ͱ����ˣ� 
	if(isRed(x->left) && isRed(x->right))	flipColors(x);
	
	x->size = size(x->left) + size(x->right) + 1; 
}

/*******************APIʵ��******************/
template <typename T, typename Comp>
void RedBlackTree<T, Comp>::insert(TreeNode* &x, const T & data){	//�ݹ顣�����Ե����ϸ���size��color�����Ե����ϲ�����ת�� 
	if(x == nullptr)	x = new TreeNode(data);
	else if(comp(x->data, data))	insert(x->right, data);
	else if(comp(data, x->data))	insert(x->left, data);
	
	balance(x);
}

// template <typename T, typename Comp>
// void RedBlackTree<T, Comp>::remove(TreeNod* &x, const T & data){
	
// }

/****************�����������****************/
template <typename T, typename Comp>
void RedBlackTree<T, Comp>::inOrderTraversal(){
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp){
			s.push(temp);
			temp = temp->left;
		}
		if(s.empty())	break;
		temp = s.top();	s.pop();
		std::cout << temp->data << " -> size: " << temp->size << " -> color: " << (temp->color==BLACK?"BLACK":"RED") << std::endl;
		temp = temp->right;
	}
}

#endif

int main()
{
	RedBlackTree<int> rbtree;
	rbtree.insert(3);
	rbtree.insert(5);
	rbtree.insert(6);
	rbtree.insert(8);
	rbtree.inOrderTraversal();
	return 0;
}
