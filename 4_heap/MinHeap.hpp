#ifndef _HEAP_H_
#define _HEAP_H_
#include <iostream>
#include <vector>
using namespace std;

//二叉堆，使用数组。 	//性质：所有root都小于它的两个child。 
template <typename T, typename Comp = std::less<T>>
class MinPQ{
private:
	Comp comp;
	int totalSize;
	vector<T> data;
private:
	void upfloat(int k);	//插入在最后边后，把末元素上浮。 
	void sink(int k);	//删除最小值root之后，把末元素交换，之后下沉末元素。 
public:
	explicit MinPQ(Comp & comp);	//自定义的比较器对象 
	explicit MinPQ(int capacity = 100);
	explicit MinPQ(const vector<T> & items);
public:
	bool isEmpty() const;
	const T & getMin() const;
	void insert(T const & x);
	int getIndex(T const & x);
	void changeValue(int index, T const & x);	//x是被替换值。 
	void deleteMin();
	void makeEmpty();
	void printAll();
};

#endif 

