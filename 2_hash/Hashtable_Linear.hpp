#ifndef _HASH_LINEAR_H_
#define _HASH_LINEAR_H_
#include "Hash.hpp"
#include "HashContainer.hpp" 
#include <iostream>
#include <vector>
using namespace std;

//线性探测法 Linear-Probing-HashTable	这里采用 
template <typename HashObj>
class HashTable{
private:
	vector<HashContainer<HashObj>> v;
	int current_size = 0;
	Hash<HashObj> hash;
private:
	void rehash(size_t capacity);
public:
	explicit HashTable(int size = 10): v(size){};
public:
	size_t getHashPos(const HashObj & x); //使用 除法哈希 得到余数并确定应该放在HashTable哪个位置。 
	void insert(const HashObj & x);
	void remove(const HashObj & x);
	bool contains(const HashObj & x);
	void makeEmpty();
	void print();
};

#endif
