#ifndef _TRIE_H_
#define _TRIE_H_
#include <iostream>
#include <string>
using namespace std;
#define CHARSET ('z'-'a'+1)

/**
 *	Trie ǰ׺�������ֵ����� 
 *	ѧϰ��Դ: http://blog.csdn.net/v_july_v/article/details/6897097
 *  ֻ�漰26����ĸ������ 
 */

class Trie{
public:
	struct TreeNode{
		char c;
		int count;
		TreeNode* next[CHARSET];
		
		TreeNode(char c): c(c), count(0), next{nullptr}{}
	}; 
private:
	TreeNode* root;
private:
	void printAll(TreeNode* x, int level);
public:
	Trie(): root(new TreeNode(' ')){}	//�Կո��ַ���Ϊ��ʼ�ڵ㡣 Ҳ���Ǵ�Trie�ĵڶ��㿪ʼ�������������塣
	void insert(const string & s){ insert(s.c_str()); };
	void insert(const char* s);
	int findWordCount(const string & s){ findWordCount(s.c_str()); }
	int findWordCount(const char* s);
	void printAll(){ printAll(root, 0); }
};

#endif
