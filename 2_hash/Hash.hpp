#ifndef _HASH_H_
#define _HASH_H_
#include <iostream>
#include "HashContainer.hpp"
using namespace std;

template <typename HashObj>
class Hash{
public:
	size_t operator()(const HashObj & key);	//��û��ʵ�� 
};

template <>
class Hash<string>{
public:
	size_t operator()(const string & key){
		size_t hashVal = 0;
		for(char ch : key){
			hashVal = hashVal * 37 + ch;	//hash_value*37 + ch��
				//Ҳ����˵hash_valueÿ�ζ�Ҫ��37������Ҳ��Java Hashԭ�� 
		}
		return hashVal; 
	}
};

#endif 
