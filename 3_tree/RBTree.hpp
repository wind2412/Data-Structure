#ifndef _RBTREE_H_
#define _RBTREE_H_
#include <iostream>
using namespace std;

#define RED 	0
#define BLACK 	1

/**
 *	红黑树。
 *  思路学自：1.https://zh.wikipedia.org/wiki/%E7%BA%A2%E9%BB%91%E6%A0%91 
 *			  2.http://blog.csdn.net/v_JULY_v/article/details/6105630 
 *  代码完全来源于wikipedia。因为正处于学习阶段，学习明白了之后加上了诸多注释和理解。 
 *	但是wikipedia的做法是自底向上进行旋转。为了和本作之前AVL树等API保持一致，故而使用自顶向下旋转方法。
 *	即，传入顶结点参数然后对子节点进行旋转。 
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
		static TreeNode* NIL;	//NIL不要忘了。NIL必须是所有叶节点的左右公共nullptr指针。也就是整个树变得“连通了”。
		
		TreeNode(T data, TreeNode* parent, TreeNode* left = NIL, TreeNode* right = NIL)	//NIL要设为static，要不这里设置不了。。 
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
//	TreeNode* TreeNode::NIL = new TreeNode(-1, nullptr);	//切记不能定义在这里。因为要static变量要定义在“namespace scope”中。 
private:
	Comp comp;
	TreeNode* root = nullptr; 
public:
	RBTree() = default;
	~RBTree(){ make_empty(root); }
private:
	void make_empty(TreeNode* x);
	TreeNode* find_left_max(TreeNode* x);	//找到此节点左子树最大值（删除含有双子的节点时） 
	void rotate_left(TreeNode* x);
	void rotate_right(TreeNode* x);
	void insert(TreeNode* x, const T & data);	//由于还要指向parent。。。所以还要返回值啊。。。 看来只要是线索树就要“预测”左右节点啊。。 
	void remove(TreeNode* x, const T & data);	//见代码实现吧。。。 
	void remove_one_child(TreeNode* x); 
	void balance_insert(TreeNode* x);
	void balance_remove(TreeNode* x);
public:
	void insert(const T & data)/*{ insert(root, data); }*/;//线索树插入不能实现得那么简单。。。因为要预判。。有些工作放在入口函数好些，其实不妨也行。 
	void remove(const T & data){ remove(root, data); };	   //但是删除是OK的。因为删除时每个节点都已经连上父亲了。不会出现找不到的情况。
	void inOrderTraversal(); 
	void preOrderTraversal(); 
};

template <typename T, typename Comp>	//注意这里要显示规定左右儿子！！是nullptr！！不能使用默认的构造！要不会死循环！
										//http://stackoverflow.com/questions/41339584/c-error-invalid-use-of-qualified-name 
typename RBTree<T, Comp>::TreeNode* RBTree<T, Comp>::TreeNode::NIL = new TreeNode(-1, nullptr, nullptr, nullptr);

#endif
