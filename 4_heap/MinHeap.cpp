#ifndef _HEAP_IMPL_H_
#define _HEAP_IMPL_H_
#include "MinHeap.hpp"
 
/**************���캯��****************/
template <typename T, typename Comp>
MinPQ<T, Comp>::MinPQ(Comp & comp) : comp(comp){
	data.push_back(T{});	//��һ��λ���ǲ��ܱ�ʹ�õģ��±��1��ʼ��
	totalSize = 0; 
}

template <typename T, typename Comp>
MinPQ<T, Comp>::MinPQ(int capacity){
	data.reserve(capacity + 1);	//��һ��λ���ò��ˡ� 
	data.push_back(T{});	//��һ��λ���ǲ��ܱ�ʹ�õģ��±��1��ʼ��
	totalSize = 0; 
}

template <typename T, typename Comp>
MinPQ<T, Comp>::MinPQ(const vector<T> & v){
	data.push_back(T{});
	totalSize = v.size();
	for(typename vector<T>::const_iterator i = v.begin(); i < v.end(); ++ i){
		data.push_back(*i);	//�����ݽ��в�������� 
	}
	for(int k = totalSize/2; k > 1; k --){	//���̫�����������ȫ����������˳��Զ��������һ��parent�����Ŷ�����sink�� 
		sink(k);
	}
}

/**************��������****************/
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

/**************��Ҫ����***************/
template <typename T, typename Comp>
void MinPQ<T, Comp>::insert(T const & x){
	data.push_back(x);	//�ں�߼��ϣ� 
	totalSize ++;
	upfloat(totalSize);
}

template <typename T, typename Comp>
const T & MinPQ<T, Comp>::getMin() const{
	return data[1];
}

template <typename T, typename Comp>
void MinPQ<T, Comp>::deleteMin(){
	if(isEmpty()) return;	//ֻ��һ��Ԫ��ʱ���±�Ҳ�ܹ������Լ����Լ������� 
	swap(data[1], data[totalSize]);
	data.pop_back();
	totalSize --;
	sink(1);
}

/**************��������**************/
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
	if(comp(value, data[index])){	//ʹ�ñȽ�������Dijkstra�����������ʹ�õ�����Ȼ��㲢û�иı䣬�����ⲿvector�е�Ȩֵ�ı��ˡ� 
		data[index] = value;		//��㱾�����仯�����������ⲿȨֵ�ı仯����ɸýڵ���Ҫ�ϸ�/�³��� 
		upfloat(index);				//��˱���ʹ�ñȽ������бȽϡ���Ȼ��ʹ�ñȽ����Ƚ�ҲӦ���ǻ���ԭ�� 
	}
	else if(comp(value, data[index])){
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
	MinPQ<int> m;	//�޲ι��캯�����ܼ����š��������򱨴���֡��� 
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
