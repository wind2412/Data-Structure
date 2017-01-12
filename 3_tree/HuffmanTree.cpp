#ifndef _HUFFMAN_IMPL_H_
#define _HUFFMAN_IMPL_H_
#include "HuffmanTree.hpp"

template <typename T, typename Comp>
Comp HuffmanTree<T, Comp>::comp;	//static����һ��Ҫ�������ʼ��������Ҫ������֮��.o�ļ��ر�����LINK1029���󣡼�����죡 

template <typename T, typename Comp>
using TreeNode = typename HuffmanTree<T, Comp>::TreeNode;

template <typename T, typename Comp>
template <typename ITER>
HuffmanTree<T, Comp>::HuffmanTree(ITER begin, ITER end){
	while(begin != end){
		TreeNode* temp = new TreeNode(*begin++, nullptr, nullptr);
		this->nodes.push(temp);	//���캯������ֻ��һ���������ҷ�explicit������ֱ����Ȩ�ر�ɶ��� 
	}
	this->size = nodes.size(); 
	if(size == 0){
		return;
	}
	if(size == 1){
		root = nodes.top(); nodes.pop();
		return;
	}
	while(nodes.size() > 1){	//��������������ʱ��������ֻ��1��ֵֻ�����ֻʣ��һ�����ո��ڵ������� 
		TreeNode* first  = nodes.top(); nodes.pop();
		TreeNode* second = nodes.top(); nodes.pop();
		TreeNode* newNode = new TreeNode(first->weight + second->weight, first, second);	//�����ڶ��ϣ�����һ���Ӻ͵Ľ�㲢�Ұ�first��second����������������
		nodes.push(newNode);
	}
	root = nodes.top(); nodes.pop();
}

template <typename T, typename Comp>
void HuffmanTree<T, Comp>::print(){	//������� 
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
