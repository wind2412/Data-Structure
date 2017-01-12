#ifndef _SORT_IMPL_H_
#define _SORT_IMPL_H_
#include <cstring>
#include <string>
#include "Sort.hpp"

template <>
int Sort<int, std::less<int>>::maxbit(){
	//��ȡ���ֵ 
	int max = a[0];
	for(int i = 1; i < n; i ++){
		if(max < a[i])	max = a[i];
	}
	//�õ����λ
	int maxbit = 0;
	while(max > 0){
		max /= 10;
		maxbit ++;
	}
	return maxbit;
}

template <>
int Sort<string, std::less<string>>::maxbit(){
	//��ȡ��󳤶�
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
	if(count != 0) cout << "    �ܼƽ���" << count << "��." << endl; 
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
	int index;	//ѡ��sedgewick���� 
	for(index = 0; index < 6; index ++){	//�Բ� ������Ϊѭ���ڲ�д�� int index = 0 ���Ե��˺þúþá��� 
		if(SedgeWick[index] < n)	break;
	}
	
	int gap = SedgeWick[index];
	for( ; gap > 0; gap = SedgeWick[++index]){
		for(int i = gap; i < n; i ++){	//ע����i++���� 
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
	
	//��ʱlo->mid   mid+1->hi�Ѿ�ȫ��������һ�𣬼������ˡ���Ϊ�ڵײ�ĵݹ��У�����mergeҲ��ʹ�������� 
	merge(src, temp, lo, mid, hi);	//lo->mid    mid+1->hi 
}

template <typename T, typename Comp>
void Sort<T, Comp>::merge(int * src, int * temp, int lo, int mid, int hi){
	int pos = lo;	//д��temp������±� 
	int i, j;
	for(i = lo, j = mid+1; i <= mid && j <= hi; /*i++, j++*/){	//ע��ӡ���ǧ���д������Ϊһ����i++��һ����j++������ 
		if(comp(src[i], src[j]))		temp[pos++] = src[i++];
		else 							temp[pos++] = src[j++];
	}
	while(i <= mid)	temp[pos++] = src[i++];
	while(j <= hi)	temp[pos++] = src[j++];
	//���Ҫ����copy��ȥ�������˹鲢��ǰ����src��ǰһ��ͺ�һ���������src���Ǳ���ԭ���Ĳ��䣬�ǿ϶����ԡ� 
	for(int i = lo; i <= hi; i ++){
		src[i] = temp[i];
	}
}

template <>
void Sort<int , std::less<int>>::bucket_sort(){	//���Ǽ�������ԭ������ͬ�� 
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
	int m = maxbit();	//��ȡintֵ�����λ��	�м�λ�ż�����	����mֻ��������  
	int len = n;		//����Ҫ��ıȽϺò���233 
	//��������ʼ
	int buc[10], temp[len];
	int radix = 1;	//����ɸѡÿ�ֵ�λ��
	for(int t = 0; t < m; t ++){	//����m���������ζԸ�λ��ʮλ����λ���в������� 
		for(int i = 0; i < 10; i ++)		buc[i] = 0;		//���Ͱ 
		for(int i = 0; i < len; i ++)		buc[(a[i] / radix) % 10]++;	//��Ͱ�����
		for(int i = 1; i < 10; i ++)		buc[i] += buc[i-1];	//�ۼ�buc
		for(int i = len-1; i >= 0; i--)		temp[--buc[(a[i] / radix) % 10]] = a[i];	//�����򡿰������a�������buc��ָ���Ż�temp�У�
		for(int i = 0; i < len; i ++)		a[i] = temp[i];	//copy��ԭ����a���顣 
		radix *= 10;
	}
	print(__func__);
}

template<>
void Sort<string, std::less<string>>::radix_sort(){
	int m = maxbit();	
	int len = n;
	int buc[127]; 	//ascii�ַ���
	string temp[len];	
	//��ֵ��ʽ����thisָ�롣i����a[i]������i��string��t����string=>a[i]�ĵ�tλ���˦˱�ʾ���t��������±꣬�ͷ���\0. 
	auto && get_bit = [this](int i, int t)->char {return (t > this->a[i].size()-1) ? '\0' : this->a[i][t]; };  //Ҫд&&������ 
	for(int t = m - 1; t >= 0; t --){	//ע��һ��Ҫ�����Ҫ��λ��ʼ�ţ�����˺�int��radix��ͬ��int����radix��������������Ҫt����string����Ҫt������ 
		for(int i = 0; i < 127; i ++)		buc[i] = 0;
		for(int i = 0; i < len; i ++)		buc[get_bit(i, t) - '\0']++;
		for(int i = 1; i < 127; i ++)		buc[i] += buc[i-1];
		for(int i = len-1; i >= 0; i--)		temp[--buc[get_bit(i, t) - '\0']] = std::move(a[i]);	//move��ֵ���á�
		for(int i = 0; i < len; i ++)		a[i] = std::move(temp[i]); 
	}
	print(__func__);
}

//heap_sort˼�룺Ҫ��С->��������򣬾�Ҫ�ȴ�n/2->1��СԪ��sink�����������ѣ��������Ѿ������->С�����ˡ�
//Ȼ�������ΰ����һ��Ԫ�غ����(��)Ԫ��exch.֮�󲻶�sink(��������˰��ܴ�Сsize-1������Ϊ���Ԫ�Ѿ�����󣬲��ù��ˡ�)��
//���൱���ǲ���deleteMin�ˡ�
template <typename T, typename Comp>
void Sort<T, Comp>::heap_sort(){ 
	int size = n; 
	auto && sink = [this, &size](int k){	//ע������Ķ����������±��0��ʼ����
		while(2*k + 1 <= size - 1){	//ֻҪ��һ�����ӣ��Ϳ���sink����������Ҷ��ӣ�����������Ҷ�ڵ�֮ʱ�˳� 
			int j = 2*k + 1;
			if(j < size-1 && comp(a[j], a[j+1]))	j++;	//��ʹ���ҲҪѡ�ұߵģ����������ұߵı����С����ȫ���ϴ�->С�����򣡣�?
			if(!comp(a[k], a[j])) break;
			swap(k, j);	 
			k = j;
		}
	};
	for(int k = size/2 - 1; k >= 0; k --){
		sink(k);
	}
//	print(__func__);
	while(size > 0){	//�൱��deleteMin�ı����С�ѣ� 
		swap(0, size---1);	//size�Լ����� 
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
