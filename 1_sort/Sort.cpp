#ifndef _SORT_IMPL_H_
#define _SORT_IMPL_H_
#include <cstring>
#include <string>
#include "Sort.hpp"

template <>
int Sort<int, std::less<int>>::maxbit(){
	//获取最大值 
	int max = a[0];
	for(int i = 1; i < n; i ++){
		if(max < a[i])	max = a[i];
	}
	//得到最高位
	int maxbit = 0;
	while(max > 0){
		max /= 10;
		maxbit ++;
	}
	return maxbit;
}

template <>
int Sort<string, std::less<string>>::maxbit(){
	//获取最大长度
	int maxlen = a[0].size();
	for(int i = 1; i < n; i ++){
		int len = a[i].size();
		if(maxlen < len)	maxlen = len;
	} 
	return maxlen;
} 

template <typename T, typename Comp>
Sort<T, Comp>::Sort(T a[], int n): n(n), a(new T[n]){
	for(int i = 0; i < n ; i ++){
		this->a[i] = a[i];
	}
}

template <typename T, typename Comp>
void Sort<T, Comp>::swap(int t1, int t2){
	T temp = std::move(a[t1]);
	a[t1] = std::move(a[t2]);
	a[t2] = std::move(temp);
}

template <typename T, typename Comp>
void Sort<T, Comp>::print(const char* func){
	std::string space(18 - strlen(func), ' ');
	cout << func << ": " << space;
	for(int i = 0; i < n; i ++){
		cout << a[i] << " "; 
	}
	if(count != 0) cout << "    总计交换" << count << "次." << endl; 
	else cout << endl;
}

template <typename T, typename Comp>
void Sort<T, Comp>::bubble_sort(){
	bool sorted = false;
	for(int i = 0; i < n - 1 && !sorted ; i ++){
		sorted = true;
		for(int j = 0; j < n - 1 - i; j ++){
			if(comp(a[j+1], a[j])){
				swap(j, j+1);
				count++;
				sorted = false;
			}
		}
	}
	print(__func__);
}

template <typename T, typename Comp>
void Sort<T, Comp>::selection_sort(){
	for(int i = 0; i < n - 1; i ++){
		for(int j = i + 1; j < n; j ++){
			if(comp(a[j], a[i])){
				swap(j, i);
				count++;
			}
		}
	}
	print(__func__);
}

template <typename T, typename Comp>
void Sort<T, Comp>::insertion_sort(){
	for(int i = 1; i < n; i ++){
		T temp = std::move(a[i]);
		int j;
		for(j = i - 1; j >= 0; j --){
			if(comp(temp, a[j])){
				a[j+1] = std::move(a[j]);
				count++;
			}
			else break;
		}
		a[j+1] = std::move(temp); 
	}
	print(__func__);
}

template <typename T, typename Comp>
void Sort<T, Comp>::shell_sort(){
	int SedgeWick[6]{109, 41, 19, 5, 1, 0};
	int index;	//选定sedgewick增量 
	for(index = 0; index < 6; index ++){	//卧槽 仅仅因为循环内部写了 int index = 0 调试调了好久好久。。 
		if(SedgeWick[index] < n)	break;
	}
	
	int gap = SedgeWick[index];
	for( ; gap > 0; gap = SedgeWick[++index]){
		for(int i = gap; i < n; i ++){	//注意是i++！！ 
			T temp = std::move(a[i]);
			int j;
			for(j = i - gap; j >= 0; j -= gap){
				if(comp(temp, a[j])){
					a[j+gap] = std::move(a[j]);
					count++;
				}
				else break;
			}
			a[j+gap] = std::move(temp);	
		}
	}
	print(__func__);
}

template <typename T, typename Comp>
void Sort<T, Comp>::quick_sort(){
	quick_sort(0, n-1);
	print(__func__);
}

template <typename T, typename Comp>
void Sort<T, Comp>::quick_sort(int lo, int hi){
	if(lo >= hi)	return;
	
	int i = lo;
	int j = hi;
	T key = a[lo];
	
	while(i < j){
		while(i < j && !comp(a[j], key))	--j;
		while(i < j && !comp(key, a[i]))	++i;
		if(i < j) {	swap(i, j);  count++; }
	}
	
	a[lo] = a[i];
	a[i] = std::move(key);	count++;
	
	quick_sort(lo, i-1);
	quick_sort(i+1, hi);
}

template <typename T, typename Comp>
void Sort<T, Comp>::merge_sort(){
	int * temp = new int[n];
	merge_sort(a, temp, 0, n-1);
	print(__func__);
}

template <typename T, typename Comp>
void Sort<T, Comp>::merge_sort(int * src, int * temp, int lo, int hi){
	if(lo >= hi)	return;
	
	int mid = (lo + hi) / 2;
	merge_sort(src, temp, lo, mid);
	merge_sort(src, temp, mid+1, hi);
	
	//此时lo->mid   mid+1->hi已经全部整合在一起，即有序了。因为在底层的递归中，不断merge也会使它们有序。 
	merge(src, temp, lo, mid, hi);	//lo->mid    mid+1->hi 
}

template <typename T, typename Comp>
void Sort<T, Comp>::merge(int * src, int * temp, int lo, int mid, int hi){
	int pos = lo;	//写到temp数组的下标 
	int i, j;
	for(i = lo, j = mid+1; i <= mid && j <= hi; /*i++, j++*/){	//注意坑。。千万别写。。因为一会是i++，一会是j++。。。 
		if(comp(src[i], src[j]))		temp[pos++] = src[i++];
		else 							temp[pos++] = src[j++];
	}
	while(i <= mid)	temp[pos++] = src[i++];
	while(j <= hi)	temp[pos++] = src[j++];
	//最后不要忘了copy回去！别忘了归并的前提是src的前一半和后一半有序！如果src还是保持原来的不变，那肯定不对。 
	for(int i = lo; i <= hi; i ++){
		src[i] = temp[i];
	}
}

template <>
void Sort<int , std::less<int>>::bucket_sort(){	//或是计数排序，原理几乎类同。 
	int * buckets = new int[n];
	for(int i = 0; i < n; i ++){
		buckets[i] = 0;
	}
	for(int i = 0; i < n; i ++){
		buckets[a[i]]++;
	}
	int pos = 0;
	for(int i = 0; i < n; i ++){
		for(int j = 1; j <= buckets[i]; j ++){
			a[pos++] = i;
		}
	} 
	print(__func__);
}

template <>
void Sort<int, std::less<int>>::radix_sort(){
	int m = maxbit();	//获取int值的最高位数	有几位排几次序	这里m只是轮数。  
	int len = n;		//名称要起的比较好才行233 
	//基数排序开始
	int buc[10], temp[len];
	int radix = 1;	//用来筛选每轮的位数
	for(int t = 0; t < m; t ++){	//进行m次排序，依次对个位，十位，百位进行不断排序。 
		for(int i = 0; i < 10; i ++)		buc[i] = 0;		//清空桶 
		for(int i = 0; i < len; i ++)		buc[(a[i] / radix) % 10]++;	//向桶里放入
		for(int i = 1; i < 10; i ++)		buc[i] += buc[i-1];	//累加buc
		for(int i = len-1; i >= 0; i--)		temp[--buc[(a[i] / radix) % 10]] = a[i];	//【逆向】把数组从a的最后经由buc的指引放回temp中！
		for(int i = 0; i < len; i ++)		a[i] = temp[i];	//copy回原来的a数组。 
		radix *= 10;
	}
	print(__func__);
}

template<>
void Sort<string, std::less<string>>::radix_sort(){
	int m = maxbit();	
	int len = n;
	int buc[127]; 	//ascii字符数
	string temp[len];	
	//以值形式捕获this指针。i代表a[i]，即第i个string。t代表string=>a[i]的第t位。此λ表示如果t超出最大下标，就返回\0. 
	auto && get_bit = [this](int i, int t)->char {return (t > this->a[i].size()-1) ? '\0' : this->a[i][t]; };  //要写&&。。。 
	for(int t = m - 1; t >= 0; t --){	//注意一定要从最不重要的位开始排！！因此和int的radix不同，int的用radix变量，根本不需要t，而string的需要t辅助。 
		for(int i = 0; i < 127; i ++)		buc[i] = 0;
		for(int i = 0; i < len; i ++)		buc[get_bit(i, t) - '\0']++;
		for(int i = 1; i < 127; i ++)		buc[i] += buc[i-1];
		for(int i = len-1; i >= 0; i--)		temp[--buc[get_bit(i, t) - '\0']] = std::move(a[i]);	//move右值引用。
		for(int i = 0; i < len; i ++)		a[i] = std::move(temp[i]); 
	}
	print(__func__);
}

//heap_sort思想：要从小->大进行排序，就要先从n/2->1把小元素sink下来构建最大堆，这样就已经满足大->小排序了。
//然后再依次把最后一个元素和最大(首)元素exch.之后不断sink(这里别忘了把总大小size-1！！因为最大元已经到最后，不用管了。)。
//就相当于是不断deleteMin了。
template <typename T, typename Comp>
void Sort<T, Comp>::heap_sort(){ 
	int size = n; 
	auto && sink = [this, &size](int k){	//注意这里的堆排序！数组下标从0开始！！
		while(2*k + 1 <= size - 1){	//只要有一个儿子，就可以sink。如果无左右儿子，即它自身是叶节点之时退出 
			int j = 2*k + 1;
			if(j < size-1 && comp(a[j], a[j+1]))	j++;	//即使相等也要选右边的！这是让最右边的变成最小，完全符合大->小的排序！！?
			if(!comp(a[k], a[j])) break;
			swap(k, j);	 
			k = j;
		}
	};
	for(int k = size/2 - 1; k >= 0; k --){
		sink(k);
	}
//	print(__func__);
	while(size > 0){	//相当于deleteMin的变成最小堆！ 
		swap(0, size---1);	//size自减勿忘 
		sink(0);
	}
	print(__func__);
}

#endif

int main()
{
	int a[10]{3,4,1,5,4,1,5,7,0,0};
	string b[10]{"bad", "habit", "makes", "a person", "worse", "please", "breed", "your", "good", "habit!"};
	Sort<int>(a, 10).bubble_sort();
	Sort<int>(a, 10).selection_sort();
	Sort<int>(a, 10).insertion_sort();
	Sort<int>(a, 10).shell_sort();
	Sort<int>(a, 10).quick_sort();
	Sort<int>(a, 10).bucket_sort();
	Sort<int>(a, 10).merge_sort();
	Sort<int>(a, 10).radix_sort();
	Sort<string>(b, 10).radix_sort();
	Sort<int>(a, 10).heap_sort();
}
