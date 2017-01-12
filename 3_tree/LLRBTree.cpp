#ifndef _RBTREE_IMPL_H_
#define _RBTREE_IMPL_H_
#include "LLRBTree.hpp"
#include <stack>

template <typename T, typename Comp>
using TreeNode = typename RedBlackTree<T, Comp>::TreeNode;

/*****************基本函数*******************/ 
template <typename T, typename Comp>
int RedBlackTree<T, Comp>::size(TreeNode* x){
	return x == nullptr ? 0 : x->size;
}

template <typename T, typename Comp>
bool RedBlackTree<T, Comp>::isRed(TreeNode* x){	//nullptr结点当成黑色！最底下的全是黑色别忘了！ 
	if(x == nullptr)	return false;
	return x->color == RED;
}

/*****************重要函数*******************/
template <typename T, typename Comp>	//左旋、右旋的条件应该都是：两个节点之间的线段是RED。 
void RedBlackTree<T, Comp>::rotateLeft(TreeNode* &x){	//左旋，必须是x->right->color == RED. 
	TreeNode* temp = x->right;
	x->right = temp->left;
	temp->left = x;
	temp->color = x->color;
	x->color = RED;
	x->size = temp->size;
	temp->size = size(temp->left) + size(temp->right) + 1;
	x = temp;	//注意千万要加这句！赋给根节点~！ 
	return;
}

template <typename T, typename Comp>
void RedBlackTree<T, Comp>::rotateRight(TreeNode* &x){	//右旋。红黑树中没有使用直接右旋的，此函数作为别的函数的基础。//左旋的镜像。 
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
	if(isRed(x->left) && isRed(x->left->left))	rotateRight(x);	//这个漂亮！x->left->left崩溃的可能性（即x->left==nullptr）的可能性在isRed(x->left)就崩溃了！ 
	if(isRed(x->left) && isRed(x->right))	flipColors(x);
	
	x->size = size(x->left) + size(x->right) + 1; 
}

/*******************API实现******************/
template <typename T, typename Comp>
void RedBlackTree<T, Comp>::insert(TreeNode* &x, const T & data){	//递归。可以自底向上更新size，color并且自底向上不断旋转。 
	if(x == nullptr)	x = new TreeNode(data);
	else if(comp(x->data, data))	insert(x->right, data);
	else if(comp(data, x->data))	insert(x->left, data);
	
	balance(x);
}

// template <typename T, typename Comp>
// void RedBlackTree<T, Comp>::remove(TreeNod* &x, const T & data){
	
// }

/****************中序遍历测试****************/
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
