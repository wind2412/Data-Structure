#ifndef _HUFFMAN_IMPL_H_
#define _HUFFMAN_IMPL_H_
#include "HuffmanTree.hpp"

template <typename T, typename Comp>
Comp HuffmanTree<T, Comp>::comp;	//static变量一定要在这里初始化啊！！要不链接之后.o文件回报类似LINK1029错误！极其诡异！ 

template <typename T, typename Comp>
using TreeNode = typename HuffmanTree<T, Comp>::TreeNode;

template <typename T, typename Comp>
template <typename ITER>
HuffmanTree<T, Comp>::HuffmanTree(ITER begin, ITER end){
	while(begin != end){
		TreeNode* temp = new TreeNode(*begin++, nullptr, nullptr);
		this->nodes.push(temp);	//构造函数可以只有一个参数，且非explicit，可以直接由权重变成对象。 
	}
	this->size = nodes.size(); 
	if(size == 0){
		return;
	}
	if(size == 1){
		root = nodes.top(); nodes.pop();
		return;
	}
	while(nodes.size() > 1){	//创建哈夫曼树的时候，数组中只有1个值只有最后只剩下一个最终根节点的情况。 
		TreeNode* first  = nodes.top(); nodes.pop();
		TreeNode* second = nodes.top(); nodes.pop();
		TreeNode* newNode = new TreeNode(first->weight + second->weight, first, second);	//必须在堆上，创建一个加和的结点并且把first和second赋给它的两个儿子
		nodes.push(newNode);
	}
	root = nodes.top(); nodes.pop();
}

template <typename T, typename Comp>
void HuffmanTree<T, Comp>::print(){	//先序遍历 
	stack<TreeNode*> s;
	TreeNode* temp = root; 
	while(true){
		while(temp){
			cout << temp->weight << " ";
			s.push(temp);
			temp = temp->left;
		}
		if(s.empty())	break;
		temp = s.top(); s.pop();
		temp = temp->right;
	}
}

template <typename T, typename Comp>
HuffmanTree<T, Comp>::~HuffmanTree(){
	makeEmpty(root);
} 

template <typename T, typename Comp>
void HuffmanTree<T, Comp>::makeEmpty(TreeNode* x){
	if(x){
		makeEmpty(x->left);
		makeEmpty(x->right);
		delete x;
	}
}

#endif 

int main()
{
	int a[]{10, 20, 30, 40};
	HuffmanTree<int, less<int>> ht(a, a+4);
	ht.print();	
} 
