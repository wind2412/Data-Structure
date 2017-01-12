#ifndef _HASH_LINEAR_IMPL_H_
#define _HASH_LINEAR_IMPL_H_
#include "Hashtable_Linear.hpp"
#include <string>

template <typename HashObj>
size_t HashTable<HashObj>::getHashPos(const HashObj & x){
	return hash(x) % v.size(); 
}

template <typename HashObj>
void HashTable<HashObj>::insert(const HashObj & x){
	size_t pos = getHashPos(x);
	//如果vector直接盛装HashObj，不是指针，那就根本没法判断那个对象是否存在！！除了指针拥有nullptr，其他类型不能用！所以必须在HashObj中包装一个isUsed！！ 
	for(; v[pos].isUsed != false; pos = (pos + 1)%v.size()){	//全都占用就一直向下线性搜索。 
		if(v[pos].obj == x){	//如果已经存过，就返回了。 循环之内注意一定要【判等！】 
			return;
		}
	}	
	v[pos].obj = x;	//循环之外再【赋值！】	//整个循环就是为了【找位置！】 
	v[pos].isUsed = true;
	current_size ++;	//注意每调用一次insert都会++！！！【陷阱！！！】 
	if(current_size > v.capacity()/2){
		rehash(v.capacity()*2);	//必须使用capacity！！因为没有存满！有unUsed！！但是链表不同，链表全是占用vector空间的！ 
	}
}

template <typename HashObj>
void HashTable<HashObj>::remove(const HashObj & x){
	size_t pos = getHashPos(x);
	if(!contains(x))	return;	//先用contains()检测一下。因为写在一起比较麻烦，其实也可以不这么写。 
	
	for(; v[pos].isUsed != false; pos = (pos + 1)%v.size()){
		if(v[pos].obj == x){
			break;
		}
	} 
	v[pos].isUsed = false;	//变为未使用。
	current_size --;
	
	pos = (pos + 1) % v.size();	//向前移位。 
	while(v[pos].isUsed != false){	//为什么要将一个键簇全部重置？一个键簇就是指从一个null右边到另一个null之间的所有元素。而且有可能超出末端从头开始。
		v[pos].isUsed = false;	//先置删除。 
		insert(v[pos].obj);
		current_size--;//【别忘了这TM是个坑。。。每次insert()默认current_size要++。。。。】 
		pos = (pos + 1) % v.size(); 
	} 
	
	if(current_size != 0 && current_size < v.capacity()/8){	//小于capacity的1/8就重新换容器。 
		rehash(v.capacity()/2);
	}
	
} 

template <typename HashObj>
bool HashTable<HashObj>::contains(const HashObj & x){
	size_t pos = getHashPos(x);
	for(; v[pos].isUsed != false; pos = (pos + 1)%v.size()){
		if(v[pos].obj == x){
			return true;
		}
	}
	return false;
}

template <typename HashObj>
void HashTable<HashObj>::makeEmpty(){
	v.clear();
}

template <typename HashObj>
void HashTable<HashObj>::rehash(size_t capacity){
	HashTable<HashObj> newHashTable(capacity);
	for(HashContainer<HashObj> & x : v){
		if(x.isUsed == true)			//千万别忘了这句！ 因为有标志位，所以不一样！而且分离链表全是链表，必须全都加入！！ 
			newHashTable.insert(x.obj);
	}
//	this->v = newHashTable.v;	//原来如此。。。vector的拷贝构造是直接把值全赋过去。。而如果newHashTable.capacity太小，也不会改变this->v的capacity。
								//而只是值的赋值而已。所以capacity根本不变！！ 
//	this->v.reserve(capacity);	//这句缩容不管用。。。
	std::swap(this->v, newHashTable.v);	//终极绝招！swap！ 啊哈哈哈哈哈！！ 
}

template <typename HashObj>
void HashTable<HashObj>::print(){
	cout << "***************************************" << endl;
	cout << "current_size: " << this->current_size << "    vector capacity: " << this->v.capacity() << endl;
	for(HashContainer<HashObj> & x : v){
		if(x.isUsed == true)
			cout << x.obj << " " << endl;
	}
	cout << endl;
	cout << "***************************************" << endl;
}

#endif

int main()
{
	HashTable<string> ht(5);
	ht.insert("hello!");
	ht.insert("world!");
	ht.insert("h");
	ht.insert("he");
	ht.insert("hel");
	ht.insert("hell");
	ht.insert("hello");
	ht.remove("hello!");
	ht.remove("hel");
	cout << ht.contains("hel") << endl;
	cout << ht.contains("hello") << endl;
	ht.remove("h");
	ht.remove("he");
	ht.remove("hello");
	ht.remove("hell");
	ht.print();
}
