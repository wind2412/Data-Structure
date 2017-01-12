#ifndef _LEFTIST_HEAP_H_
#define _LEFTIST_HEAP_H_
#include <iostream>
using namespace std;

/**
 *	左式堆。	http://www.cnblogs.com/pacoson/p/5142330.html 
 *				可视化工具： http://www.u396.com/wp-content/collection/data-structure-visualizations/LeftistHeap.html 
 */
template <typename T, typename Comp = std::less<T>>
class LeftistHeap{
public:
	struct TreeNode{
		T data;
		TreeNode* left;
		TreeNode* right;
		int npl;	//null pointer length 零路径长。 
		
		TreeNode(T data, TreeNode* left = nullptr, TreeNode* right = nullptr)
										:data(data), left(left), right(right), npl(0){}; 
	};
private:
	TreeNode* root = nullptr;
	Comp comp;
private:
	void merge(LeftistHeap & rhs);	//接受另一棵左偏树作为参数 并合并
	TreeNode* merge(TreeNode* h1, TreeNode* h2);	//必须返回TreeNode！！即使 传参TreeNode*&也不行！！因为无法找到每一层的根节点。不知道会被根节点会是左树 
	TreeNode* innerMerge(TreeNode* h1, TreeNode* h2);	//还是右树。思考起来太麻烦，不如统一返回啊。 
	void swap(TreeNode* x);	//swap左右子树
	int npl(TreeNode* x);	//得到npl
public:
	void insert(const T & data);
	T getMin();
	void deleteMin(); 
	void preOrderTraversal();
}; 



#endif
