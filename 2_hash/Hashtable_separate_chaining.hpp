#ifndef _HASH_LIST_H_
#define _HASH_LIST_H_
#include "Hash.hpp" 
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

template <typename HashObj>	//����Hash����������ϣֵ�� 
class Hash;

//ʹ��������β�����н����[�������ӷ�]HashTable. 
template <typename HashObj>
class HashTable{
private:
	vector<list<HashObj>> lists;
	int current_size = 0;
	Hash<HashObj> hash;	//���ڲ���hashֵ��hash���� 
private:
	void rehash();
public:
	explicit HashTable(int size = 100): lists(size){};
public:
	size_t getHashPos(const HashObj & x); //ʹ�� ������ϣ �õ�������ȷ��Ӧ�÷���HashTable�ĸ�λ�á� 
	void insert(const HashObj & x);
	void remove(const HashObj & x);
	bool contains(const HashObj & x);
	void makeEmpty();
	void print();
};

#endif 
