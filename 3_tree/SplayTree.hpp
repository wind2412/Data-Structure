#ifndef _SPLAY_TREE_
#define _SPLAY_TREE_
#include <iostream>
using namespace std;

//the programming information is from: https://zh.wikipedia.org/wiki/%E4%BC%B8%E5%B1%95%E6%A0%91
//SplayTree���ӽڵ����root��ת����Ϊ�������ģ�������ָ��parent��ָ�롣�����ӽڵ�ͱ�����ȥ�ˡ� 
template <typename T, typename Comp = std::less<T>>
class SplayTree{
private:
	Comp comp;	//�Ƚ����� 
	unsigned size; //����С�� 
	struct SplayNode{
		T data;
		SplayNode* left, * right;
		SplayNode* parent;	//Ҫ�͸��ڵ㽻���� 
		SplayNode(T data, SplayNode* parent = nullptr, SplayNode* left = nullptr, SplayNode* right = nullptr)
			:parent(parent), data(data), left(left), right(right){}; 
	}*root = nullptr;
private:	//6�������ת��
	void zig_only(SplayNode* x);  //���û������(grandfather)��㣬��ֻ��һ��zig/zag. => left_rotate()
	void zag_only(SplayNode* x);  //���� => right_rotate()
	void zig_zig(SplayNode* x);	  //��������[/]���Ρ�Ҫֱ�ӱ��[\]���Ρ� 
	void zig_zag(SplayNode* x);	  //��[<]���Ρ����[>]���Ρ� 
	void zag_zig(SplayNode* x);	  //���� 
	void zag_zag(SplayNode* x);	  //���� 
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
	void replace(SplayNode* x, SplayNode* y);	//��x��parent��ָ���x�滻��y�� 
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
 
