#ifndef _LEFTIST_HEAP_IMPL_H_
#define _LEFTIST_HEAP_IMPL_H_
#include "LeftistHeap.hpp"
#include <stack>
#include <algorithm>

template <typename T, typename Comp>
using TreeNode = typename LeftistHeap<T, Comp>::TreeNode;

template <typename T, typename Comp>
void LeftistHeap<T, Comp>::swap(TreeNode* x){
	TreeNode* temp = x->left;
	x->left = x->right;
	x->right = temp; 
}

template <typename T, typename Comp>
int LeftistHeap<T, Comp>::npl(TreeNode* x){
	if(x == nullptr)	return -1;
	else return x->npl;
}

template <typename T, typename Comp>
void LeftistHeap<T, Comp>::merge(LeftistHeap & rhs){	//��Ҫ�����������������Ӻ�����ڡ� 
	if(this == &rhs)	return;	//����mergeͬһ����
	root = merge(root, rhs.root);	//���ұߵ�merge����ߣ�Ȼ������ұߡ� 
}

template <typename T, typename Comp>	//�ɶԡ����ӻ����ݽṹ���Ĺ۲�д��  //http://www.u396.com/wp-content/collection/data-structure-visualizations/LeftistHeap.html 
typename LeftistHeap<T, Comp>::TreeNode* LeftistHeap<T, Comp>::merge(TreeNode* h1, TreeNode* h2){
	if(h1 == nullptr)		return h2;	//�ݹ�� 	�������npl 
	else if(h2 == nullptr)	return h1;	//�ݹ�� 	�������npl 
	else if(comp(h1->data, h2->data)){	//�������������ǰ�С����right�ʹ�������merge��Ȼ�󷵻ظ��ڵ㣡 
		h1->right = merge(h1->right, h2);	
		h1->npl = min(npl(h1->left), npl(h1->right)) + 1;
		if(npl(h1->left) < npl(h1->right))	swap(h1);
		return h1;
	}
	else {
		h2->right = merge(h2->right, h1);
		h2->npl = min(npl(h2->left), npl(h2->right)) + 1;
		if(npl(h2->left) < npl(h2->right))	swap(h2);
		return h2;
	}
} 

/***************�����ݽṹ���㷨����������********************/
/**template <typename T, typename Comp>
typename LeftistHeap<T, Comp>::TreeNode* LeftistHeap<T, Comp>::merge(TreeNode* h1, TreeNode* h2){	//�Ѹ�С��TreeNode�ŵ���ߡ��������Ӻ�����ڡ� 
	if(h1 == nullptr)		return h2;	//�ݹ�� 
	else if(h2 == nullptr)	return h1;	//�ݹ�� 
	else if(comp(h1->data, h2->data))	return innerMerge(h1, h2);
	else 								return innerMerge(h2, h1);	//��ȵ�����Ҳ�����ˡ� 
}

template <typename T, typename Comp>
typename LeftistHeap<T, Comp>::TreeNode* LeftistHeap<T, Comp>::innerMerge(TreeNode* h1, TreeNode* h2){	//Ŀǰh1�Ǹ��ڵ��С������ 
	//ע�����if����Ϊ�൱��ֱ�Ӳ��뵽h1���ұߣ�Ȼ������npl���⣨this->left->npl < this->right->npl�����Ҫswap�������ڵ�npl��û���£�����
	//���������������൱��ֱ������߲����ˣ��������Ż�������ǶԳ�ѧ�ߺܲ��Ѻþ����ˡ��� 
	if(h1->left == nullptr) h1->left = h2;	//ֻ�н��Ϊ�Լ���h1	//��npl������Ҫ���¡�	//��Ϊthis->npl�����ҽ��npl��Сֵ+1. ���ҽ��nullptr->npl=-1.���this->npl����0. 
	else{
		//h2��root�͸���h1��С����right����merge().
		h1->right = merge(h1->right, h2);
		
		//�ݹ����npl
		h1->npl = std::min(npl(h1->left), npl(h1->right)) + 1;
		//���npl < �ұ�npl    �򽻻���    ��Ϊ���nplһ��Ҫ�����ұ�npl������ƫ���� 
		if(npl(h1->left) < npl(h2->right))	swap(h1);	 
	}
	return h1;
}*/
/*************************************************************/

template <typename T, typename Comp>
void LeftistHeap<T, Comp>::insert(const T & data){
	root = merge(root, new TreeNode(data));
}

template <typename T, typename Comp>
T LeftistHeap<T, Comp>::getMin(){
	return root->data;
}

template <typename T, typename Comp>
void LeftistHeap<T, Comp>::deleteMin(){
	TreeNode* temp = root;
	root = merge(root->left, root->right);
	delete temp;
}

template <typename T, typename Comp>
void LeftistHeap<T, Comp>::preOrderTraversal(){
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp){
			cout << temp->data << " ";
			s.push(temp);
			temp = temp->left;
		}
		if(s.empty())	break;
		temp = s.top(); s.pop();
		temp = temp->right; 
	}
}

#endif

int main()
{
	LeftistHeap<int> l;
	l.insert(3);
	l.insert(5);
	l.insert(8);
	l.insert(4); 
	l.insert(9);
	l.insert(3);
	
//	cout << l.getMin() << endl;
//	l.deleteMin();
	l.preOrderTraversal();	
}
