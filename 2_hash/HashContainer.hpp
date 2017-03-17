#ifndef _HASH_CONTAINER_H_
#define _HASH_CONTAINER_H_ 
#include <iostream>
using namespace std;

//由于vector中直接存入对象（非指针）无法判断vector中该slot槽中是否已经赋过值。比如里边是乱码314342314，但是没准我赋值就是这个，因而没法判断。
//因而需要包装，重新加入一个新的变量isUsed. 
template <typename HashObj>
class HashContainer{
public:
	HashObj obj;
	bool isUsed = false;
public:
	HashContainer() = default;
};

#endif 
