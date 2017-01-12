#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

template <typename Pointer>
class Less;	//��С������ 
/**
 * ����������
 * ��Ȩ��̶������������Ŷ������� 
 */
template <typename T, typename Comp = std::less<T>>
class HuffmanTree{
public:
	struct TreeNode{
		public: 
			T weight;	//����Ȩֵ 
			TreeNode* left;
			TreeNode* right;
		public:
			TreeNode(T weight, TreeNode* left = nullptr, TreeNode* right = nullptr) :weight(weight), left(left), right(right) {};
			bool operator < (TreeNode & x) const {return comp(weight, x.weight);}	//�����comp���ⲿstatic�ġ�C++�ڲ���ֻ�ܵ�����ߵ�static����������::��ԱҲ���Ե��ðɣ�û�Թ��� 
	};
private:
	static Comp comp;		//�Ƚ��� 
	TreeNode* root = nullptr;	//���ڵ� 
	//ע��������ѣ���ԽСԽ���ں�ߣ�����˱��뷴��дLess������Ҫ�����ų�40,30,20,10...... 
	priority_queue<TreeNode*, vector<TreeNode*>, Less<TreeNode*>> nodes;	//������ļ���  Ҳ������vector,deque֮�࣬������Ҫÿ������ 
	int size;
private:
	void makeEmpty(TreeNode* x);	//�ݹ�ɾ�� 
public:
	template <typename ITER>	HuffmanTree(ITER begin, ITER end);	//���캯��
	~HuffmanTree();	//��������
public: 
	void print();	//������� 
};

template <typename Pointer>
class Less{	//Ϊ���ܹ�����TreeNode*֮��ıȽ϶�д����Less�� 
public:
	bool operator()(Pointer & x, Pointer & y){
		return *y < *x;	//��Ȼ���ֽ�Less�����������Ѿ�ʵ����Great�ˡ����� 
	}
};

#endif 
