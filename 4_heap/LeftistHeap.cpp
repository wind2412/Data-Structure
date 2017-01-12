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
void LeftistHeap<T, Comp>::merge(LeftistHeap & rhs){	//主要避免重名，并且增加函数入口。 
	if(this == &rhs)	return;	//避免merge同一棵树
	root = merge(root, rhs.root);	//把右边的merge到左边，然后清空右边。 
}

template <typename T, typename Comp>	//由对《可视化数据结构》的观察写出  //http://www.u396.com/wp-content/collection/data-structure-visualizations/LeftistHeap.html 
typename LeftistHeap<T, Comp>::TreeNode* LeftistHeap<T, Comp>::merge(TreeNode* h1, TreeNode* h2){
	if(h1 == nullptr)		return h2;	//递归基 	不需更新npl 
	else if(h2 == nullptr)	return h1;	//递归基 	不需更新npl 
	else if(comp(h1->data, h2->data)){	//不管其他，就是把小树的right和大树整个merge！然后返回根节点！ 
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

/***************《数据结构与算法分析》代码********************/
/**template <typename T, typename Comp>
typename LeftistHeap<T, Comp>::TreeNode* LeftistHeap<T, Comp>::merge(TreeNode* h1, TreeNode* h2){	//把根小的TreeNode放到左边。并且增加函数入口。 
	if(h1 == nullptr)		return h2;	//递归基 
	else if(h2 == nullptr)	return h1;	//递归基 
	else if(comp(h1->data, h2->data))	return innerMerge(h1, h2);
	else 								return innerMerge(h2, h1);	//相等的条件也算上了。 
}

template <typename T, typename Comp>
typename LeftistHeap<T, Comp>::TreeNode* LeftistHeap<T, Comp>::innerMerge(TreeNode* h1, TreeNode* h2){	//目前h1是根节点较小的树。 
	//注意这个if。因为相当于直接插入到h1的右边，然后由于npl问题（this->left->npl < this->right->npl）因而要swap！而各节点npl并没更新，所以
	//这个单独的情况就相当于直接在左边插入了！！这种优化很妙，但是对初学者很不友好就是了。。 
	if(h1->left == nullptr) h1->left = h2;	//只有结点为自己的h1	//连npl都不需要更新。	//因为this->npl是左右结点npl最小值+1. 而右结点nullptr->npl=-1.因此this->npl还是0. 
	else{
		//h2的root送给把h1（小）的right重新merge().
		h1->right = merge(h1->right, h2);
		
		//递归更新npl
		h1->npl = std::min(npl(h1->left), npl(h1->right)) + 1;
		//左边npl < 右边npl    则交换。    因为左边npl一定要大于右边npl才是左偏树。 
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
