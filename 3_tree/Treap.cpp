#ifndef _TREAP_IMPL_H_
#define _TREAP_IMPL_H_
#include "Treap.hpp"
#include <stack>
#define MAX_PRIORITY 2147483647 

template <typename T, typename Comp>
using TreeNode = typename Treap<T, Comp>::TreeNode;

/**************��������********************/
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
	return x == nullptr ? MAX_PRIORITY : x->priority;	//ע���Ƿŵ����ֵ�� 
}

/***************��Ҫ����*******************/
template <typename T, typename Comp>
void Treap<T, Comp>::insert(TreeNode* &x, T data, int priority){
	if(x == nullptr)	x = new TreeNode(data, priority);
	else if(comp(x->data, data)) {
		insert(x->right, data, priority);
		if(x->priority > x->right->priority)	rotateWithRightChild(x);	//������ȼ�С���͵���ȥ�� 
	}
	else if(comp(data, x->data)) {
		insert(x->left, data, priority);
		if(x->priority > x->left->priority)		rotateWithLeftChild(x);
	}
	else	x->priority = priority;
	
	x->size = size(x->left) + size(x->right) + 1;
}

/***************���Ժ���*******************/
template <typename T, typename Comp>
void Treap<T, Comp>::inOrderTraversal(){	//�������Ĳ��뷽ʽ+������˳�����ת��ʽ 
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

template <typename T, typename Comp>	//���ϵذѴ�ɾ�ڵ���ת������£�Ȼ��ֱ��ɾ���� 
void Treap<T, Comp>::remove(TreeNode* &x, T data){	//�ö��������ұ�ɾ�㣬ʹ��priority��С�Ƚϲ���ת��ʹ�ñ�ɾ�����������ӽڵ� Ȼ��ֱ��ȥ���ӽڵ㡣 
	if(x == nullptr)	return;
	else if(comp(x->data, data))	remove(x->right, data);
	else if(comp(data, x->data))	remove(x->left,  data);
	else{	//�ﵽɾ���ص㣡Ҫ��ʼ��ת�ˣ� 
		if(!(x->left == nullptr && x->right == nullptr)){	//û����ӽڵ�֮ǰ 
			if(priority(x->left) < priority(x->right)){
				rotateWithLeftChild(x);	//�������ֵС���ұߣ������ȼ������ұߡ��������ͰѸߵ�����������x����ȥ��
				remove(x->right, data);	//������������������ұߵݹ��ȥɾ���� 
			}else {
				rotateWithRightChild(x);
				remove(x->left, data);
			}
//			x->size = size(x->left) + size(x->right) + 1;	//����������д��ԭ����һ��ʼ�Ķ�����else if��ֻ�����ĲŽ�else.�ʶ�����д����ߣ�����ô������ô���ǵĴ��� 
		}
		else{	//����ȫ�ǿգ�����ǿ���ɾ���ˡ� 
			delete x;
			x = nullptr;
		}
	}
	
	if(x != nullptr)	x->size = size(x->left) + size(x->right) + 1;
}

template <typename T, typename Comp>	//��Ҫ������������	�ͷ��ڴ氡���� 
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
				delete temp;	//����delete�������鰡����ʵ�о������������������϶��ǶԵģ� 
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
