#ifndef _TRIE_IMPL_H_
#define _TRIE_IMPL_H_
#include "Trie.hpp"
#include <cstring>

using TreeNode = typename Trie::TreeNode;

void Trie::insert(const char* s){
	int len = strlen(s);
	TreeNode* temp = root;
	for(int pos = 0; pos < len; pos ++){
		if(temp->next[s[pos]-'a'] == nullptr){	//如果位置上是空的，那么就新建节点。 
			temp->next[s[pos]-'a'] = new TreeNode(s[pos]);
		}
		temp = temp->next[s[pos]-'a'];	//字典树指针向下层更新
		if(pos == len - 1){	//已经到了单词末尾 
			temp->count ++;	//单词数+1 
		} 
	}
}

int Trie::findWordCount(const char* s){
	int len = strlen(s);
	TreeNode* temp = root;
	for(int pos = 0; pos < len; pos ++){
		if(temp->next[s[pos]-'a'] == nullptr){
			return -1;	//查无此单词。 
		}
		else{	//找到了该字符，那么就向下寻找 
			temp = temp->next[s[pos]-'a'];	//注意这个应该写在前边！！！因为找到了的话，应该要索引到那个字符的node！ 
			if(pos == len - 1){
				return temp->count;
			}
		}
	}
}

void Trie::printAll(TreeNode* x, int level){
	if(x == nullptr)	return;	//递归基 因为要一直向下递归
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
