#ifndef _HASH_LIST_IMPL_H_
#define _HASH_LIST_IMPL_H_
#include "Hashtable_separate_chaining.hpp"
#include <algorithm>

template <typename HashObj>
size_t HashTable<HashObj>::getHashPos(const HashObj & x){
	return hash(x) % lists.size(); 
}

template <typename HashObj>
void HashTable<HashObj>::insert(const HashObj & x){
	size_t pos = getHashPos(x);
	list<HashObj> & targetList = lists[pos];
	if(std::find(begin(targetList), end(targetList), x) != end(targetList))	return;	//�Ƚ��в��ҡ�����ɹ����Ͳ����롣 
	targetList.push_front(x);
	current_size ++;
	if(current_size > lists.size()){	//�������Ԫ�ص���������lists.size()���Ǿ�rehash������size = 10. ���Ѿ�������10������Ҫrehash�� 
		rehash();						//�˾��������ȵ�ƽ��ֵ����Ϊ1.�ܹ���ȫ���ٲ�ѯʱ�䡣 
	}
}

template <typename HashObj>
void HashTable<HashObj>::remove(const HashObj & x){
	size_t pos = getHashPos(x);
	list<HashObj> & targetList = lists[pos];
	auto it = std::find(begin(targetList), end(targetList), x);
	if(it == end(targetList))	return;	//û�ҵ���ɾ����
	targetList.erase(it);
	-- current_size;
} 

template <typename HashObj>
bool HashTable<HashObj>::contains(const HashObj & x){
	size_t pos = getHashPos(x);
	list<HashObj> & targetList = lists[pos];
	return (std::find(begin(targetList), end(targetList), x) != end(targetList)) ? false : true;
}

template <typename HashObj>
void HashTable<HashObj>::makeEmpty(){
	for(auto & list : lists){
		list.clear();
	}
}

template <typename HashObj>
void HashTable<HashObj>::rehash(){
	HashTable<HashObj> newHashTable(lists.size() * 2);	//ֱ���½�һ�������Ƿǳ�Ư���ģ�	//������vector.size()�ǿ��Եģ���Ϊȫ�������ˣ�ȫ������ 
	for(auto & list : lists){
		for(HashObj & x : list){
			newHashTable.insert(x);
		}
	}
//	this = &newHashTable;	//����﷨���󡣡���ֻ��һ��Ԫ��һ��Ԫ�ظ����ˡ�������
	this->lists = newHashTable.lists; 
}

template <typename HashObj>
void HashTable<HashObj>::print(){
	cout << "***************************************" << endl;
	for(auto & list : lists){
		if(list.empty())	continue;
		std::for_each(begin(list), end(list), [](const HashObj & x){
			cout << x << " ";
		});
		cout << endl;
	}
	cout << "***************************************" << endl;
}

#endif

int main()
{
	HashTable<string> ht(5);
	ht.insert("hello");
	ht.insert("world");
	ht.insert("bad");
	ht.insert("baddy");
	ht.insert("worse");
	ht.remove("hello");
	ht.remove("bad");
	ht.insert("left");
	ht.insert("right");
	ht.print();
	ht.insert("change������");
	cout << "after rehashing: " << endl; 
	ht.print();
	
}

