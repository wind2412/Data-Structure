#ifndef _SKEW_HEAP_H_
#define _SKEW_HEAP_H_
#include <iostream>
using namespace std;

/**
 * 斜堆。	和左式堆（左偏树）很像，但每个结点不保存npl，节省了空间，但是每次merge成功之后需要进行无条件swap。
 *			所有操作全在右边进行，因此如果想要保持稍稍的平衡，必须无条件进行交换，这也是结点没有npl的代价。 
 *		可视化：http://www.u396.com/wp-content/collection/data-structure-visualizations/SkewHeap.html
 *		此代码完全按照可视化的规则进行代码编辑。API借用LeftistHeap。 
 */
template <typename T, typename Comp = std::less<T>>
class SkewHeap{
public:
	struct TreeNode{
		T data;
		TreeNode* left;
		TreeNode* right;
		
		TreeNode(T data, TreeNode* left = nullptr, TreeNode* right = nullptr)
											:data(data), left(left), right(right){}; 
	};
private:
	TreeNode* root = nullptr;
	Comp comp;
private:
	void merge(SkewHeap & rhs);	
	TreeNode* merge(TreeNode* h1, TreeNode* h2);
	void swap(TreeNode* x);	
public:
	void insert(const T & data);
	T getMin();
	void deleteMin(); 
	void preOrderTraversal();
}; 


#endif 
