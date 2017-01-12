#ifndef _TRIE_IMPL_H_
#define _TRIE_IMPL_H_
#include "Trie.hpp"
#include <cstring>

using TreeNode = typename Trie::TreeNode;

void Trie::insert(const char* s){
	int len = strlen(s);
	TreeNode* temp = root;
	for(int pos = 0; pos < len; pos ++){
		if(temp->next[s[pos]-'a'] == nullptr){	//���λ�����ǿյģ���ô���½��ڵ㡣 
			temp->next[s[pos]-'a'] = new TreeNode(s[pos]);
		}
		temp = temp->next[s[pos]-'a'];	//�ֵ���ָ�����²����
		if(pos == len - 1){	//�Ѿ����˵���ĩβ 
			temp->count ++;	//������+1 
		} 
	}
}

int Trie::findWordCount(const char* s){
	int len = strlen(s);
	TreeNode* temp = root;
	for(int pos = 0; pos < len; pos ++){
		if(temp->next[s[pos]-'a'] == nullptr){
			return -1;	//���޴˵��ʡ� 
		}
		else{	//�ҵ��˸��ַ�����ô������Ѱ�� 
			temp = temp->next[s[pos]-'a'];	//ע�����Ӧ��д��ǰ�ߣ�������Ϊ�ҵ��˵Ļ���Ӧ��Ҫ�������Ǹ��ַ���node�� 
			if(pos == len - 1){
				return temp->count;
			}
		}
	}
}

void Trie::printAll(TreeNode* x, int level){
	if(x == nullptr)	return;	//�ݹ�� ��ΪҪһֱ���µݹ�
	for(int i = 0; i < level; i ++)	cout << "\t";
	if(x->c != ' ')		cout << x->c << " " << x->count << endl;
	for(int pos = 0; pos < CHARSET; pos ++){
		if(x->next[pos] != nullptr){
			printAll(x->next[pos], level+1);
		}
	} 
} 

#endif

int main()
{
	Trie t;
	t.insert(string("zebra"));
	t.insert("bad");
	t.insert("brown");
	t.insert("black");
	t.insert("bless");
	t.insert("zebra");
	t.insert("zebra");
	cout << "zebra calls " << t.findWordCount("zebra") << " times." << endl;
	t.printAll();
}
