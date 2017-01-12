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
	//���vectorֱ��ʢװHashObj������ָ�룬�Ǿ͸���û���ж��Ǹ������Ƿ���ڣ�������ָ��ӵ��nullptr���������Ͳ����ã����Ա�����HashObj�а�װһ��isUsed���� 
	for(; v[pos].isUsed != false; pos = (pos + 1)%v.size()){	//ȫ��ռ�þ�һֱ�������������� 
		if(v[pos].obj == x){	//����Ѿ�������ͷ����ˡ� ѭ��֮��ע��һ��Ҫ���еȣ��� 
			return;
		}
	}	
	v[pos].obj = x;	//ѭ��֮���١���ֵ����	//����ѭ������Ϊ�ˡ���λ�ã��� 
	v[pos].isUsed = true;
	current_size ++;	//ע��ÿ����һ��insert����++�����������壡������ 
	if(current_size > v.capacity()/2){
		rehash(v.capacity()*2);	//����ʹ��capacity������Ϊû�д�������unUsed������������ͬ������ȫ��ռ��vector�ռ�ģ� 
	}
}

template <typename HashObj>
void HashTable<HashObj>::remove(const HashObj & x){
	size_t pos = getHashPos(x);
	if(!contains(x))	return;	//����contains()���һ�¡���Ϊд��һ��Ƚ��鷳����ʵҲ���Բ���ôд�� 
	
	for(; v[pos].isUsed != false; pos = (pos + 1)%v.size()){
		if(v[pos].obj == x){
			break;
		}
	} 
	v[pos].isUsed = false;	//��Ϊδʹ�á�
	current_size --;
	
	pos = (pos + 1) % v.size();	//��ǰ��λ�� 
	while(v[pos].isUsed != false){	//ΪʲôҪ��һ������ȫ�����ã�һ�����ؾ���ָ��һ��null�ұߵ���һ��null֮�������Ԫ�ء������п��ܳ���ĩ�˴�ͷ��ʼ��
		v[pos].isUsed = false;	//����ɾ���� 
		insert(v[pos].obj);
		current_size--;//����������TM�Ǹ��ӡ�����ÿ��insert()Ĭ��current_sizeҪ++���������� 
		pos = (pos + 1) % v.size(); 
	} 
	
	if(current_size != 0 && current_size < v.capacity()/8){	//С��capacity��1/8�����»������� 
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
		if(x.isUsed == true)			//ǧ���������䣡 ��Ϊ�б�־λ�����Բ�һ�������ҷ�������ȫ����������ȫ�����룡�� 
			newHashTable.insert(x.obj);
	}
//	this->v = newHashTable.v;	//ԭ����ˡ�����vector�Ŀ���������ֱ�Ӱ�ֵȫ����ȥ���������newHashTable.capacity̫С��Ҳ����ı�this->v��capacity��
								//��ֻ��ֵ�ĸ�ֵ���ѡ�����capacity�������䣡�� 
//	this->v.reserve(capacity);	//������ݲ����á�����
	std::swap(this->v, newHashTable.v);	//�ռ����У�swap�� ���������������� 
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
