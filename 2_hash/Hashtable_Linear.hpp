#ifndef _HASH_LINEAR_H_
#define _HASH_LINEAR_H_
#include "Hash.hpp"
#include "HashContainer.hpp" 
#include <iostream>
#include <vector>
using namespace std;

//����̽�ⷨ Linear-Probing-HashTable	������� 
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
	size_t getHashPos(const HashObj & x); //ʹ�� ������ϣ �õ�������ȷ��Ӧ�÷���HashTable�ĸ�λ�á� 
	void insert(const HashObj & x);
	void remove(const HashObj & x);
	bool contains(const HashObj & x);
	void makeEmpty();
	void print();
};

#endif
