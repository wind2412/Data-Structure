#ifndef _HEAP_IMPL_H_
#define _HEAP_IMPL_H_
#include "MinHeap.hpp"
 
/**************构造函数****************/
template <typename T, typename Comp>
MinPQ<T, Comp>::MinPQ(Comp & comp) : comp(comp){
	data.push_back(T{});	//第一个位置是不能被使用的，下标从1开始。
	totalSize = 0; 
}

template <typename T, typename Comp>
MinPQ<T, Comp>::MinPQ(int capacity){
	data.reserve(capacity + 1);	//第一个位置用不了。 
	data.push_back(T{});	//第一个位置是不能被使用的，下标从1开始。
	totalSize = 0; 
}

template <typename T, typename Comp>
MinPQ<T, Comp>::MinPQ(const vector<T> & v){
	data.push_back(T{});
	totalSize = v.size();
	for(typename vector<T>::const_iterator i = v.begin(); i < v.end(); ++ i){
		data.push_back(*i);	//把数据进行插入操作。 
	}
	for(int k = totalSize/2; k > 1; k --){	//这个太妙！！由于是完全二叉树，因此除以二就是最后一个parent，倒着对所有sink！ 
		sink(k);
	}
}

/**************基本工具****************/
template <typename T, typename Comp>
void MinPQ<T, Comp>::upfloat(int k){	//after insertion
	for(; k > 1 && comp(data[k], data[k/2]); k /= 2){
		swap(data[k], data[k/2]);
	}
}

template <typename T, typename Comp>
void MinPQ<T, Comp>::sink(int k){	//after deletion
	while(k * 2 <= totalSize){
		int child = k * 2;
		if(child < totalSize && comp(data[k*2+1], data[k*2])){
			child ++ ;
		}
		if(comp(data[k], data[child]))	break;
		swap(data[k], data[child]);
		k = child;
	}
}

/**************重要函数***************/
template <typename T, typename Comp>
void MinPQ<T, Comp>::insert(T const & x){
	data.push_back(x);	//在后边加上！ 
	totalSize ++;
	upfloat(totalSize);
}

template <typename T, typename Comp>
const T & MinPQ<T, Comp>::getMin() const{
	return data[1];
}

template <typename T, typename Comp>
void MinPQ<T, Comp>::deleteMin(){
	if(isEmpty()) return;	//只有一个元素时，下边也能工作！自己和自己交换。 
	swap(data[1], data[totalSize]);
	data.pop_back();
	totalSize --;
	sink(1);
}

/**************其他函数**************/
template <typename T, typename Comp>
int MinPQ<T, Comp>::getIndex(T const & x){
	for(int i = 1; i < totalSize; i ++){
		if(x == data[i]){
			return i;
		}
	}
	return -1;
}

template <typename T, typename Comp>
void MinPQ<T, Comp>::changeValue(int index, const T & value){
	if(index < 1 || index > totalSize)	return;
	if(comp(value, data[index])){	//使用比较器。在Dijkstra中这个方法被使用到。虽然结点并没有改变，但是外部vector中的权值改变了。 
		data[index] = value;		//结点本身并不变化，但是由于外部权值的变化，造成该节点需要上浮/下沉。 
		upfloat(index);				//因此必须使用比较器进行比较。当然，使用比较器比较也应该是基本原则。 
	}
	else if(comp(data[index], value)){
		data[index] = value;
		sink(index);
	}
}

template <typename T, typename Comp>
bool MinPQ<T, Comp>::isEmpty() const{
	return totalSize == 0;
}

template <typename T, typename Comp>
void MinPQ<T, Comp>::makeEmpty(){
	data.erase(data.begin()+1, data.end());
	totalSize = 0;
}

template <typename T, typename Comp>
void MinPQ<T, Comp>::printAll(){
	for(typename vector<T>::const_iterator i = data.begin() + 1; i != data.end(); ++i){
		cout << *i << " ";
	}
	cout << endl;
}

#endif

#include <vector>

void testMinHeap()
{
	MinPQ<int> m;	//无参构造函数不能加括号。。。否则报错超奇怪。。 
	m.insert(3);
	m.insert(6);
	m.insert(2);
	m.insert(8);
	m.printAll();


	cout << "min number: " << m.getMin() << endl;
	m.deleteMin();
	m.printAll();
	m.deleteMin();
	m.printAll();
	m.deleteMin();
	m.printAll();
	m.deleteMin();
	m.printAll();
	
	cout << "is empty? " << m.isEmpty() << endl;
	
	vector<int> v{1,4,3,5,7,3,2};
	MinPQ<int> n(v);
	n.printAll();
	n.deleteMin();
	n.deleteMin();
	cout << "after two deleteMin: " << endl;
	n.printAll();
	
	int index = n.getIndex(4);
	cout << index << endl;
	n.changeValue(index, 8);
	
	n.printAll();
	n.makeEmpty();
	n.printAll();
	cout << "is empty? " << n.isEmpty() << endl;
}


// int main()
// {
// 	testMinHeap();
// }
