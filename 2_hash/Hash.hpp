#ifndef _HASH_H_
#define _HASH_H_
#include <iostream>
#include "HashContainer.hpp"
using namespace std;

template <typename HashObj>
class Hash{
public:
	size_t operator()(const HashObj & key);	//并没有实现 
};

template <>
class Hash<string>{
public:
	size_t operator()(const string & key){
		size_t hashVal = 0;
		for(char ch : key){
			hashVal = hashVal * 37 + ch;	//hash_value*37 + ch，
				//也就是说hash_value每次都要乘37倍。这也是Java Hash原则。 
		}
		return hashVal; 
	}
};

#endif 
