#ifndef _LEFTIST_HEAP_H_
#define _LEFTIST_HEAP_H_
#include <iostream>
using namespace std;

/**
 *	��ʽ�ѡ�	http://www.cnblogs.com/pacoson/p/5142330.html 
 *				���ӻ����ߣ� http://www.u396.com/wp-content/collection/data-structure-visualizations/LeftistHeap.html 
 */
template <typename T, typename Comp = std::less<T>>
class LeftistHeap{
public:
	struct TreeNode{
		T data;
		TreeNode* left;
		TreeNode* right;
		int npl;	//null pointer length ��·������ 
		
		TreeNode(T data, TreeNode* left = nullptr, TreeNode* right = nullptr)
										:data(data), left(left), right(right), npl(0){}; 
	};
private:
	TreeNode* root = nullptr;
	Comp comp;
private:
	void merge(LeftistHeap & rhs);	//������һ����ƫ����Ϊ���� ���ϲ�
	TreeNode* merge(TreeNode* h1, TreeNode* h2);	//���뷵��TreeNode������ʹ ����TreeNode*&Ҳ���У�����Ϊ�޷��ҵ�ÿһ��ĸ��ڵ㡣��֪���ᱻ���ڵ�������� 
	TreeNode* innerMerge(TreeNode* h1, TreeNode* h2);	//����������˼������̫�鷳������ͳһ���ذ��� 
	void swap(TreeNode* x);	//swap��������
	int npl(TreeNode* x);	//�õ�npl
public:
	void insert(const T & data);
	T getMin();
	void deleteMin(); 
	void preOrderTraversal();
}; 



#endif
