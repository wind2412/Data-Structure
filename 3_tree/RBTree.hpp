#ifndef _RBTREE_H_
#define _RBTREE_H_
#include <iostream>
using namespace std;

#define RED 	0
#define BLACK 	1

/**
 *	�������
 *  ˼·ѧ�ԣ�1.https://zh.wikipedia.org/wiki/%E7%BA%A2%E9%BB%91%E6%A0%91 
 *			  2.http://blog.csdn.net/v_JULY_v/article/details/6105630 
 *  ������ȫ��Դ��wikipedia����Ϊ������ѧϰ�׶Σ�ѧϰ������֮����������ע�ͺ���⡣ 
 *	����wikipedia���������Ե����Ͻ�����ת��Ϊ�˺ͱ���֮ǰAVL����API����һ�£��ʶ�ʹ���Զ�������ת������
 *	�������붥������Ȼ����ӽڵ������ת�� 
 */
template <typename T, typename Comp = std::less<T>>
class RBTree{
public:
	struct TreeNode{
		T data;
		bool color;
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent;
		static TreeNode* NIL;	//NIL��Ҫ���ˡ�NIL����������Ҷ�ڵ�����ҹ���nullptrָ�롣Ҳ������������á���ͨ�ˡ���
		
		TreeNode(T data, TreeNode* parent, TreeNode* left = NIL, TreeNode* right = NIL)	//NILҪ��Ϊstatic��Ҫ���������ò��ˡ��� 
							:data(data), color(RED), left(left), right(right), parent(parent){}
		TreeNode* sibling(){
			if(this->parent == nullptr)	return nullptr;
			return this->parent->left == this ? this->parent->right : this->parent->left; 
		} 
		TreeNode* grandparent(){
			if(this->parent == nullptr)	return nullptr;
			return this->parent->parent;
		}
		TreeNode* uncle(){
			if(this->grandparent() == nullptr)	return nullptr;
			return this->grandparent()->left == this->parent ? this->grandparent()->right : this->grandparent()->left;
		}
	};
//	TreeNode* TreeNode::NIL = new TreeNode(-1, nullptr);	//�мǲ��ܶ����������ΪҪstatic����Ҫ�����ڡ�namespace scope���С� 
private:
	Comp comp;
	TreeNode* root = nullptr; 
public:
	RBTree() = default;
	~RBTree(){ make_empty(root); }
private:
	void make_empty(TreeNode* x);
	TreeNode* find_left_max(TreeNode* x);	//�ҵ��˽ڵ����������ֵ��ɾ������˫�ӵĽڵ�ʱ�� 
	void rotate_left(TreeNode* x);
	void rotate_right(TreeNode* x);
	void insert(TreeNode* x, const T & data);	//���ڻ�Ҫָ��parent���������Ի�Ҫ����ֵ�������� ����ֻҪ����������Ҫ��Ԥ�⡱���ҽڵ㰡���� 
	void remove(TreeNode* x, const T & data);	//������ʵ�ְɡ����� 
	void remove_one_child(TreeNode* x); 
	void balance_insert(TreeNode* x);
	void balance_remove(TreeNode* x);
public:
	void insert(const T & data)/*{ insert(root, data); }*/;//���������벻��ʵ�ֵ���ô�򵥡�������ΪҪԤ�С�����Щ����������ں�����Щ����ʵ����Ҳ�С� 
	void remove(const T & data){ remove(root, data); };	   //����ɾ����OK�ġ���Ϊɾ��ʱÿ���ڵ㶼�Ѿ����ϸ����ˡ���������Ҳ����������
	void inOrderTraversal(); 
	void preOrderTraversal(); 
};

template <typename T, typename Comp>	//ע������Ҫ��ʾ�涨���Ҷ��ӣ�����nullptr��������ʹ��Ĭ�ϵĹ��죡Ҫ������ѭ����
										//http://stackoverflow.com/questions/41339584/c-error-invalid-use-of-qualified-name 
typename RBTree<T, Comp>::TreeNode* RBTree<T, Comp>::TreeNode::NIL = new TreeNode(-1, nullptr, nullptr, nullptr);

#endif
