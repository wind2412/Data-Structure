#ifndef _SKEW_HEAP_IMPL_H_
#define _SKEW_HEAP_IMPL_H_
#include "SkewHeap.hpp"
#include <stack>

template <typename T, typename Comp>
using TreeNode = typename SkewHeap<T, Comp>::TreeNode;

template <typename T, typename Comp>
void SkewHeap<T, Comp>::swap(TreeNode* x){	//ͬ��ʽ�� 
	TreeNode* temp = x->left;
	x->left = x->right;
	x->right = temp;
} 

template <typename T, typename Comp>
void SkewHeap<T, Comp>::merge(SkewHeap & rhs){	//ͬ��ʽ�� 
	if(this == &rhs)	return;	
	root = merge(root, rhs.root); 
}

template <typename T, typename Comp>	
typename SkewHeap<T, Comp>::TreeNode* SkewHeap<T, Comp>::merge(TreeNode* h1, TreeNode* h2){
	if(h1 == nullptr)		return h2;	//�ݹ�� 	 swap���½�����һ�����������˽�����������ϲ�Э��666    �����Ҿ��Ǹ��𷵻صģ� 
	else if(h2 == nullptr)	return h1;	//�ݹ�� 	 
	else if(comp(h2->data, h1->data)){	//�������������ǰ�С����right�ʹ�������merge��Ȼ�󷵻ظ��ڵ㣡 
		h2->right = merge(h2->right, h1);	//ע������߰�h2->data == h1->data�����д�ڵ�һ�����ˡ�Ϊ������ӻ��Ľ����ȫһ�¡� 
		swap(h2);							//����ʽ�ѵ�ʵ���У�Ϊ����Mr.Weiss�Ĵ�����ȫһ�£����equal�����������else�С�Ī���֡� 
	}
	else{
		h1->right = merge(h1->right, h2);
		swap(h1);
	}
} 

template <typename T, typename Comp>
void SkewHeap<T, Comp>::insert(const T & data){	//ͬ��ʽ�� 
	root = merge(root, new TreeNode(data));
}

template <typename T, typename Comp>
T SkewHeap<T, Comp>::getMin(){	//ͬ��ʽ�� 
	return root->data;
}

template <typename T, typename Comp>
void SkewHeap<T, Comp>::deleteMin(){	//ͬ��ʽ�� 
	TreeNode* temp = root;
	root = merge(root->left, root->right);
	delete temp;
}

template <typename T, typename Comp>
void SkewHeap<T, Comp>::preOrderTraversal(){	//ͬ��ʽ�� 
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
	SkewHeap<int> s;
	s.insert(3);
	s.insert(5);
	s.insert(8);
	s.insert(4); 
	s.insert(9);
	s.insert(3);
	s.insert(10);
	s.insert(65);
	s.insert(37);
	
//	cout << l.getMin() << endl;
//	l.deleteMin();
	s.preOrderTraversal();	
}
