#ifndef _SKEW_HEAP_H_
#define _SKEW_HEAP_H_
#include <iostream>
using namespace std;

/**
 * б�ѡ�	����ʽ�ѣ���ƫ�������񣬵�ÿ����㲻����npl����ʡ�˿ռ䣬����ÿ��merge�ɹ�֮����Ҫ����������swap��
 *			���в���ȫ���ұ߽��У���������Ҫ�������Ե�ƽ�⣬�������������н�������Ҳ�ǽ��û��npl�Ĵ��ۡ� 
 *		���ӻ���http://www.u396.com/wp-content/collection/data-structure-visualizations/SkewHeap.html
 *		�˴�����ȫ���տ��ӻ��Ĺ�����д���༭��API����LeftistHeap�� 
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
