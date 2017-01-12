#ifndef _HEAP_H_
#define _HEAP_H_
#include <iostream>
#include <vector>
using namespace std;

//����ѣ�ʹ�����顣 	//���ʣ�����root��С����������child�� 
template <typename T, typename Comp = std::less<T>>
class MinPQ{
private:
	Comp comp;
	int totalSize;
	vector<T> data;
private:
	void upfloat(int k);	//���������ߺ󣬰�ĩԪ���ϸ��� 
	void sink(int k);	//ɾ����Сֵroot֮�󣬰�ĩԪ�ؽ�����֮���³�ĩԪ�ء� 
public:
	explicit MinPQ(Comp & comp);	//�Զ���ıȽ������� 
	explicit MinPQ(int capacity = 100);
	explicit MinPQ(const vector<T> & items);
public:
	bool isEmpty() const;
	const T & getMin() const;
	void insert(T const & x);
	int getIndex(T const & x);
	void changeValue(int index, T const & x);	//x�Ǳ��滻ֵ�� 
	void deleteMin();
	void makeEmpty();
	void printAll();
};

#endif 

