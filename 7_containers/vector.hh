#ifndef __VECTOR_HH__
#define __VECTOR_HH__

#include <iostream>
#include <cstdlib>
#include <functional>
#include <cstring>		// 引用 memcpy，来解决 【Vector 无法接收内含 const & 成员变量的对象，因为原先的 push_back 使用了 = 进行 copy assignment。其实这样是有2个问题的。
						//                    1. 其实原先 malloc 的 this->v 就是野内存，只不过我强行用 T * 来让 C++ 把它看成了 T 对象了。但是内部全是垃圾值。某种意义说，那根本就不能叫做对象。copy assignment 其实需要左右边都是对象才行。这是语义不符合。
						//					  2. 由于对象内部含有 const &，常引用不可能更改对象的指向。所以，原先的垃圾值就不可能被 copy assignment 改变了。解决方法是，在 this->v 的地方直接就地 construct(STL的方案)，或者直接就地 memcpy(我的方案)】 的 bug。
						// 由于我没有 allocator，即没有内存池，我只能选择第二个方案。

template <typename T>		// 模板一定要声明 + 定义都在同一个文件中！！要不会链接错误......
class Vector{
private:
	int capacity;
	int num;
	T * v;
public:
	class Iterator {
	private:
		Vector<T> & v;
		int cur;
	public:
		explicit Iterator (Vector<T> & v, int cur) : v(v), cur(cur) {}
		
		Iterator operator ++ () 
		{
			cur = cur + 1;
			return *this;
		}

		Iterator operator ++ (int n) 
		{
			Iterator temp = *this;
			cur = cur + 1;
			return temp;
		}

		T & operator * () 
		{
			return v[cur];
		}

		bool operator == (const Iterator & x) const
		{
			return this->v[this->cur] == x.v[x.cur];
		}

		bool operator != (const Iterator & x) const
		{
			return this->v[this->cur] != x.v[x.cur];
		}

	};
public:
	// 注意！！这里千万要只用 malloc 不能用 new ！！因为 new 的话直接就 new T[]，这就会构造 T！！如果 T 的构造函数不是 POD，那么就会编译错误！！
	explicit Vector(int capacity = 10) : capacity(capacity), num(0), v((T*)malloc(sizeof(T) * capacity)/*new T[capacity]*/) {}	// 不能把 num 上来就设置为 10 ！！！因为如果这时要 push 的话，那岂不是要从 11 个开始吗？
	Vector(const Vector<T> & v);		// 在 main 函数 返回 Dijkstra distance Vector 的时候，出现 free 两次的情况！！原因是 Vector 进行 copy，是浅拷贝！！这里应该重写拷贝构造函数！！
	void resize(int n);
	void push_back(const T & x);
	T pop_back();
	T & back();
	void print();
	void rev_print();
	int find(const T & x);
	T & operator [] (int index);
	const T & operator [] (int index) const;
	int size() const;
	template <typename Comp = std::less<T>>		void quick_sort(Comp && comp = std::less<T>());
	~Vector();
public:
	Iterator begin ();		// 在这里加上 const 之后，好像本来没错的vector_test 也会报错了！！好好看看这里！！
	Iterator end ();		// 但是，实际上取得一个 Iterator，是可以对里边元素进行修改的。本来也不应该表上 const。
	Iterator iterator();
};

template <typename T>
Vector<T>::Vector(const Vector<T> & v)
{
	this->capacity = v.capacity;
	this->num = v.num;
	this->v = new T[this->capacity];
	for(int i = 0; i < this->num; i ++) {
		this->v[i] = v.v[i];		// 深拷贝！！！
	}
}

template <typename T>
void Vector<T>::resize(int n)
{
	T * newbuf = (T*) malloc (sizeof(T) * n);
	for(int i = 0; i < this->num; i ++){
		// newbuf[i] = this->v[i];		// 【【【这里的 = 赋值也有问题！！应该在容器的构造中，禁止使用 = 赋值构造！！！】】】
		memcpy(&newbuf[i], &this->v[i], sizeof(T));		// 改成 memcpy 就对了！！
	}
	this->capacity = n;
	free(this->v);
	this->v = newbuf;
}

template <typename T>
void Vector<T>::push_back(const T & x)
{
	if(num < capacity){		// 写错成了 <= 导致了 bug......
		// this->v[num++] = x;		// 这里的 copy assignment 是本次 Vector 的最大陷阱！！千万不能这么写！！见最上边的说明！要不没法传递 内含 const & 成员的对象！！
		// 要改成 memcpy。
		memcpy(&this->v[num++], &x, sizeof(x));		// 应该就没问题了。
	} else {
		resize(capacity * 2);
		push_back(x);	// 递归重新进行 push
	}
}

template <typename T>
T Vector<T>::pop_back()
{
	if(num == 0) {
		std::cout << "there is no elem in vector!" << std::endl;
		// 直接崩溃就好。
	}
	T temp = this->v[--num];
	if (num <= capacity / 4)	resize (capacity / 2);
	return temp;
}

template <typename T>
void Vector<T>::print()
{
	for(int i = 0; i < num; i ++){
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

// template <>
// void Vector<std::wstring>::print()
// {
// 	for(int i = 0; i < num; i ++){
// 		std::wcout << v[i] << " ";
// 	}
// 	std::cout << std::endl;
// }

template <typename T>
void Vector<T>::rev_print()
{
	for(int i = num-1; i >= 0; i --){
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

// template <>
// void Vector<std::wstring>::rev_print()
// {
// 	for(int i = num-1; i >= 0; i --){
// 		std::wcout << v[i] << " ";
// 	}
// 	std::cout << std::endl;
// }

template <typename T>
Vector<T>::~Vector()
{
	// std::cout << this << std::endl;
	// delete [] this->v;
	free(this->v);
}

template <typename T>
T & Vector<T>::operator [] (int index)
{
	return this->v[index];
}

template <typename T>
const T & Vector<T>::operator [] (int index) const 
{
	return this->v[index];
}

template <typename T>
T & Vector<T>::back ()
{
	if(num == 0) {
		std::cout << "there is no elem in vector!" << std::endl;
		// 直接崩溃就好。
	}
	return this->v[num - 1];
}

template <typename T>
int Vector<T>::find (const T & x)
{
	for(int i = 0; i < this->num; i ++){
		if(this->v[i] == x){
			return x;
		}
	}
	return -1;
}

template <typename T>
int Vector<T>::size () const
{
	return this->num;
}

template <typename T>
template <typename Comp>
void Vector<T>::quick_sort (Comp && comp)
{
	std::function<void(int, int)> real_quick_sort = [this, &comp, &real_quick_sort] (int lo, int hi) {
		if(lo >= hi)	return;
		
		int i = lo;
		int j = hi;
		T key = this->v[lo];
		
		while(i < j){
			while(i < j && !comp(this->v[j], key))	--j;
			while(i < j && !comp(key, this->v[i]))	++i;
			if(i < j) {	std::swap(this->v[i], this->v[j]); }
		}
		
		this->v[lo] = this->v[i];
		this->v[i] = std::move(key);
		
		real_quick_sort(lo, i-1);
		real_quick_sort(i+1, hi);
	};

	real_quick_sort(0, this->size()-1);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin()
{
	return Iterator(*this, 0);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end()
{
	return Iterator(*this, this->num);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::iterator()
{
	return Iterator(*this, 0);
}

#endif