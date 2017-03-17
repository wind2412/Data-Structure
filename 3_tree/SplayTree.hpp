#ifndef _SPLAY_TREE_
#define _SPLAY_TREE_
#include <iostream>
using namespace std;

//the programming information is from: https://zh.wikipedia.org/wiki/%E4%BC%B8%E5%B1%95%E6%A0%91
//SplayTree是子节点控制root旋转。因为是线索的，所以有指向parent的指针。这样子节点就被弹上去了。 
template <typename T, typename Comp = std::less<T>>
class SplayTree{
private:
	Comp comp;	//比较器。 
	unsigned size; //树大小。 
	struct SplayNode{
		T data;
		SplayNode* left, * right;
		SplayNode* parent;	//要和父节点交互。 
		SplayNode(T data, SplayNode* parent = nullptr, SplayNode* left = nullptr, SplayNode* right = nullptr)
			:parent(parent), data(data), left(left), right(right){}; 
	}*root = nullptr;
private:	//6种情况旋转。
	void zig_only(SplayNode* x);  //如果没有祖先(grandfather)结点，就只做一次zig/zag. => left_rotate()
	void zag_only(SplayNode* x);  //镜像。 => right_rotate()
	void zig_zig(SplayNode* x);	  //成三个点[/]字形。要直接变成[\]字形。 
	void zig_zag(SplayNode* x);	  //成[<]字形。变成[>]字形。 
	void zag_zig(SplayNode* x);	  //镜像。 
	void zag_zag(SplayNode* x);	  //镜像。 
private:	//helping--tools
	void preorderTraversal(SplayNode* t){
		if(t != nullptr){
			cout << t->data << " ";
			preorderTraversal(t->left);
			preorderTraversal(t->right);
		}
	}
	void inorderTraversal(SplayNode* t){
		if(t != nullptr){
			inorderTraversal(t->left);
			cout << t->data << " ";
			inorderTraversal(t->right);
		}
	}
	void splay(SplayNode* x); 
	void replace(SplayNode* x, SplayNode* y);	//把x的parent所指向的x替换成y。 
public:
	SplayTree() = default;
	SplayNode* find(T const & );
	void insert(T const & );
	void remove(T const & );
	bool isEmpty(){return size == 0;}
public: 	//tools--for test
	ostream & preorderTraversal(){
		cout << "root = " << root->data << endl; 
		preorderTraversal(root);
		return cout;
	}
	ostream & inorderTraversal(){
		cout << "root = " << root->data << endl; 
		inorderTraversal(root);
		return cout;
	}
};

#endif
 
