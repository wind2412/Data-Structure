#ifndef _SORT_H_
#define _SORT_H_
#include <iostream>
using namespace std;

template <typename T, typename Comp = std::less<T>>
class Sort{
private:
	Comp comp;
	int n;	//数组长度 
	T * a;
	int count = 0;	//总计交换次数。 
public:
	Sort(T a[], int n);
private:
	int maxbit();
	void swap(int t1, int t2);
	void print(const char * func);
private:
	void quick_sort(int lo, int hi);
	void merge_sort(int * src, int * temp, int lo, int hi);
	void merge(int * src, int * temp, int lo, int mid, int hi);
public:
	void bubble_sort();
	void selection_sort();
	void insertion_sort();
	void shell_sort();
	void quick_sort();
	void quick_3_sort();	
	void merge_sort();
	void bucket_sort(); 
	void radix_sort();	//【?】基数排序从最个位->最高位排，就能得到正确结果。为什么？？感觉应该是保持了什么的相对位置不变？ 
	void heap_sort();	//【?】为什么会成功？？？ 
};

#endif 
