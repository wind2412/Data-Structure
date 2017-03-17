#ifndef _TREAP_IMPL_H_
#define _TREAP_IMPL_H_
#include "Treap.hpp"
#include <stack>
#define MAX_PRIORITY 2147483647 

template <typename T, typename Comp>
using TreeNode = typename Treap<T, Comp>::TreeNode;

/**************基础函数********************/
template <typename T, typename Comp>
void Treap<T, Comp>::rotateWithLeftChild(TreeNode* &x){	//right-rotation
	TreeNode* temp = x->left;
	x->left = temp->right;
	temp->right = x;
	x = temp;
}

template <typename T, typename Comp>
void Treap<T, Comp>::rotateWithRightChild(TreeNode* &x){
	TreeNode* temp = x->right;
	x->right = temp->left;
	temp->left = x;
	x = temp;
} 

template <typename T, typename Comp>
int Treap<T, Comp>::size(TreeNode* &x){
	return x == nullptr ? 0 : x->size;
}

template <typename T, typename Comp>
int Treap<T, Comp>::priority(TreeNode* &x){
	return x == nullptr ? MAX_PRIORITY : x->priority;	//注意是放到最大值！ 
}

/***************重要函数*******************/
template <typename T, typename Comp>
void Treap<T, Comp>::insert(TreeNode* &x, T data, int priority){
	if(x == nullptr)	x = new TreeNode(data, priority);
	else if(comp(x->data, data)) {
		insert(x->right, data, priority);
		if(x->priority > x->right->priority)	rotateWithRightChild(x);	//如果优先级小，就调上去。 
	}
	else if(comp(data, x->data)) {
		insert(x->left, data, priority);
		if(x->priority > x->left->priority)		rotateWithLeftChild(x);
	}
	else	x->priority = priority;
	
	x->size = size(x->left) + size(x->right) + 1;
}

/***************测试函数*******************/
template <typename T, typename Comp>
void Treap<T, Comp>::inOrderTraversal(){	//二叉树的插入方式+调整堆顺序的旋转方式 
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp){
			s.push(temp);
			temp = temp->left;
		}
		if(s.empty())	break;
		temp = s.top(); s.pop();
		cout << "data->" << temp->data << " priority->" << temp->priority << " size->" << temp->size << endl;
		temp = temp->right;
	}
}

template <typename T, typename Comp>	//不断地把待删节点旋转到最底下，然后直接删除！ 
void Treap<T, Comp>::remove(TreeNode* &x, T data){	//用二叉树查找被删点，使用priority大小比较并旋转堆使得被删除点移至最子节点 然后直接去除子节点。 
	if(x == nullptr)	return;
	else if(comp(x->data, data))	remove(x->right, data);
	else if(comp(data, x->data))	remove(x->left,  data);
	else{	//达到删除地点！要开始旋转了！ 
		if(!(x->left == nullptr && x->right == nullptr)){	//没变成子节点之前 
			if(priority(x->left) < priority(x->right)){
				rotateWithLeftChild(x);	//左边优先值小于右边，即优先级大于右边。这样，就把高的提上来。把x降下去。
				remove(x->right, data);	//发生了右旋，因此上右边递归地去删除。 
			}else {
				rotateWithRightChild(x);
				remove(x->left, data);
			}
//			x->size = size(x->left) + size(x->right) + 1;	//不能在这里写。原因是一开始的都进的else if。只有最后的才进else.故而必须写在外边，，怎么还犯这么弱智的错。。 
		}
		else{	//两边全是空，因此是可以删除了。 
			delete x;
			x = nullptr;
		}
	}
	
	if(x != nullptr)	x->size = size(x->left) + size(x->right) + 1;
}

template <typename T, typename Comp>	//不要忘了析构！！	释放内存啊！！ 
Treap<T, Comp>::~Treap(){
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp){
			s.push(temp);
			temp = temp->left;
		}
		TreeNode* q = nullptr;
		while(!s.empty()){
			temp = s.top(); s.pop();
			if(temp->right == q){
				delete temp;	//这里delete还是心虚啊。其实感觉并不明晰，但是它肯定是对的！ 
				q = temp;
			}
			else{
				s.push(temp);
				temp = temp->right;
				break;
			}
		}
		if(s.empty())	break;
	}
}

#endif

int main()
{
	Treap<int> t;
	t.insert(3, 10);
	t.insert(5, 8);
	t.insert(4, 20);
	t.insert(9, 0);
	t.inOrderTraversal(); cout << endl;
	t.remove(3);
	t.remove(4);
	t.remove(5);
	t.inOrderTraversal();
	
}
