#ifndef _HASH_CONTAINER_H_
#define _HASH_CONTAINER_H_ 
#include <iostream>
using namespace std;

//����vector��ֱ�Ӵ�����󣨷�ָ�룩�޷��ж�vector�и�slot�����Ƿ��Ѿ�����ֵ���������������314342314������û׼�Ҹ�ֵ������������û���жϡ�
//�����Ҫ��װ�����¼���һ���µı���isUsed. 
template <typename HashObj>
class HashContainer{
public:
	HashObj obj;
	bool isUsed = false;
public:
	HashContainer() = default;
};

#endif 
