#ifndef _HASH_LIST_H_
#define _HASH_LIST_H_
#include "Hash.hpp" 
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

template <typename HashObj>	//声明Hash辅助产生哈希值类 
class Hash;

//使用链表在尾部进行接入的[分离链接法]HashTable. 
template <typename HashObj>
class HashTable{
private:
	vector<list<HashObj>> lists;
	int current_size = 0;
	Hash<HashObj> hash;	//用于产生hash值的hash对象。 
private:
	void rehash();
public:
	explicit HashTable(int size = 100): lists(size){};
public:
	size_t getHashPos(const HashObj & x); //使用 除法哈希 得到余数并确定应该放在HashTable哪个位置。 
	void insert(const HashObj & x);
	void remove(const HashObj & x);
	bool contains(const HashObj & x);
	void makeEmpty();
	void print();
};

#endif 
