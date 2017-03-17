#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

template <typename Pointer>
class Less;	//最小类声明 
/**
 * 哈夫曼树：
 * 带权最短二叉树，即最优二叉树。 
 */
template <typename T, typename Comp = std::less<T>>
class HuffmanTree{
public:
	struct TreeNode{
		public: 
			T weight;	//结点的权值 
			TreeNode* left;
			TreeNode* right;
		public:
			TreeNode(T weight, TreeNode* left = nullptr, TreeNode* right = nullptr) :weight(weight), left(left), right(right) {};
			bool operator < (TreeNode & x) const {return comp(weight, x.weight);}	//这里的comp是外部static的。C++内部类只能调用外边的static？？用类名::成员也可以调用吧，没试过。 
	};
private:
	static Comp comp;		//比较器 
	TreeNode* root = nullptr;	//根节点 
	//注意这个最大堆！！越小越排在后边！！因此必须反着写Less。。。要不会排成40,30,20,10...... 
	priority_queue<TreeNode*, vector<TreeNode*>, Less<TreeNode*>> nodes;	//待排序的集合  也可以用vector,deque之类，但是需要每轮排序。 
	int size;
private:
	void makeEmpty(TreeNode* x);	//递归删除 
public:
	template <typename ITER>	HuffmanTree(ITER begin, ITER end);	//构造函数
	~HuffmanTree();	//析构函数
public: 
	void print();	//先序遍历 
};

template <typename Pointer>
class Less{	//为了能够做到TreeNode*之间的比较而写出的Less类 
public:
	bool operator()(Pointer & x, Pointer & y){
		return *y < *x;	//虽然名字叫Less。。。但是已经实际是Great了。。。 
	}
};

#endif 
