#ifndef _SKEW_HEAP_IMPL_H_
#define _SKEW_HEAP_IMPL_H_
#include "SkewHeap.hpp"
#include <stack>

template <typename T, typename Comp>
using TreeNode = typename SkewHeap<T, Comp>::TreeNode;

template <typename T, typename Comp>
void SkewHeap<T, Comp>::swap(TreeNode* x){	//同左式堆 
	TreeNode* temp = x->left;
	x->left = x->right;
	x->right = temp;
} 

template <typename T, typename Comp>
void SkewHeap<T, Comp>::merge(SkewHeap & rhs){	//同左式堆 
	if(this == &rhs)	return;	
	root = merge(root, rhs.root); 
}

template <typename T, typename Comp>	
typename SkewHeap<T, Comp>::TreeNode* SkewHeap<T, Comp>::merge(TreeNode* h1, TreeNode* h2){
	if(h1 == nullptr)		return h2;	//递归基 	 swap的事交给上一个调用它的人解决！！交给上层协议666    ——我就是负责返回的！ 
	else if(h2 == nullptr)	return h1;	//递归基 	 
	else if(comp(h2->data, h1->data)){	//不管其他，就是把小树的right和大树整个merge！然后返回根节点！ 
		h2->right = merge(h2->right, h1);	//注：这里边把h2->data == h1->data的情况写在第一个中了。为了与可视化的结果完全一致。 
		swap(h2);							//在左式堆的实现中，为了与Mr.Weiss的代码完全一致，因此equal的情况放在了else中。莫见怪。 
	}
	else{
		h1->right = merge(h1->right, h2);
		swap(h1);
	}
} 

template <typename T, typename Comp>
void SkewHeap<T, Comp>::insert(const T & data){	//同左式堆 
	root = merge(root, new TreeNode(data));
}

template <typename T, typename Comp>
T SkewHeap<T, Comp>::getMin(){	//同左式堆 
	return root->data;
}

template <typename T, typename Comp>
void SkewHeap<T, Comp>::deleteMin(){	//同左式堆 
	TreeNode* temp = root;
	root = merge(root->left, root->right);
	delete temp;
}

template <typename T, typename Comp>
void SkewHeap<T, Comp>::preOrderTraversal(){	//同左式堆 
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
