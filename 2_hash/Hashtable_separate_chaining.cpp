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
	if(std::find(begin(targetList), end(targetList), x) != end(targetList))	return;	//先进行查找。如果成功，就不插入。 
	targetList.push_front(x);
	current_size ++;
	if(current_size > lists.size()){	//如果已有元素的数量大于lists.size()，那就rehash。比如size = 10. 我已经储存了10个，就要rehash。 
		rehash();						//此举让链表长度的平均值仅仅为1.能够完全减少查询时间。 
	}
}

template <typename HashObj>
void HashTable<HashObj>::remove(const HashObj & x){
	size_t pos = getHashPos(x);
	list<HashObj> & targetList = lists[pos];
	auto it = std::find(begin(targetList), end(targetList), x);
	if(it == end(targetList))	return;	//没找到不删除。
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
	HashTable<HashObj> newHashTable(lists.size() * 2);	//直接新建一个对象是非常漂亮的！	//这里用vector.size()是可以的！因为全都存满了！全是链表！ 
	for(auto & list : lists){
		for(HashObj & x : list){
			newHashTable.insert(x);
		}
	}
//	this = &newHashTable;	//雾草语法错误。。。只能一个元素一个元素更换了。。。。
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
	ht.insert("change！！！");
	cout << "after rehashing: " << endl; 
	ht.print();
	
}

