#ifndef __VECTOR_HH__
#define __VECTOR_HH__

#include <iostream>
#include <cstdlib>
#include <functional>
#include <cstring>		
						// 原先的思考[1]，已经被 deprecated (废弃) 了。
						// 引用 memcpy，来解决 【Vector 无法接收内含 const & 成员变量的对象，因为原先的 push_back 使用了 = 进行 copy assignment。其实这样是有2个问题的。
						//                    1. 其实原先 malloc 的 this->v 就是野内存，只不过我强行用 T * 来让 C++ 把它看成了 T 对象了。但是内部全是垃圾值。某种意义说，那根本就不能叫做对象。copy assignment 其实需要左右边都是对象才行。这是语义不符合。
						//					  2. 由于对象内部含有 const &，常引用不可能更改对象的指向。所以，原先的垃圾值就不可能被 copy assignment 改变了。解决方法是，在 this->v 的地方直接就地 construct(STL的方案)，或者直接就地 memcpy(我的方案)】 的 bug。
						// 由于我没有 allocator，即没有内存池，我只能选择第二个方案。于是即为 malloc 和 memcpy 的组合进行构造。

// 最终的思考。采用。
// 编写 vector 时，要注意考虑几种情况：
// 1. 如果 T 类型的对象中 含有 const & 的常引用 ==>  然而查了一遭，这东西确实使用了 = 。但是是 “复制构造”， 而不是 “复制赋值”。
// 2. 如果 T 是 string/vector 自身的情况  ==>  STL 的 alloc 用来分配内存。然后用 = 进行 “复制构造”。同时，不可以使用 memcpy。因为这就相当于 “浅拷贝” ！！可以使用 sizeof。对象的大小也是确定的。
// 3. 可以用 sizeof，因为即便是 C++ 对象，运行时大小肯定是确定的。不能确定的只能是在堆上 new 出来的东西。其实 new 出来的东西大小也是确定的啊。只不过可以通过 delete + 再new 进行 “扩容”。
// 我最终使用了 malloc 和 replacement new 的组合。放弃了 malloc 和 = 的组合、 new 和 = 的组合，以及 malloc 和 memcpy 的组合。
// [•]下边的注释全是当时思考的过程。画 [×] 的全都是废弃的方案。画 [√] 的是最终采用的方案。
// 唉。STL 实在是博大精深啊。连一个构造函数我都要仔细思考好几天。这是由多少个菊苣们一起设计出来的精华啊。
// 用一个 constructor 来进行 replacement new 的封装。而且，使用泛型的原因，是为了获得参数的类型！！【泛型还有这种用处！！】

template <typename Tp, typename Arg1>
void __constructor(Tp *ptr, const Arg1 & arg1)		// 适配一个参数
{
	::new ((void *)ptr) Tp(arg1);
}

template <typename Tp, typename Arg1, typename Arg2>
void __constructor(Tp *ptr, const Arg1 & arg1, const Arg2 & arg2)		// 适配两个参数
{
	::new ((void *)ptr) Tp(arg1, arg2);
}

template <typename Tp, typename Arg1, typename Arg2, typename Arg3>
void __constructor(Tp *ptr, const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3)		// 适配三个参数
{
	::new ((void *)ptr) Tp(arg1, arg2, arg3);
}

template <typename Tp, typename ...Args>
void constructor(Tp *ptr, Args &&...args) 
{
	__constructor(ptr, std::forward<Args>(args)...);		// 完美转发变长参数
}

template <typename Tp>
void destructor(Tp *ptr)
{
	ptr->~Tp();		// replacement new 也是需要析构的。要不然，对象没法回收了。因为并没有句柄啊。所以 编译器判断不出来一个对象出没出作用域，是否死亡。这 new 就相当于“永久代” 了。
}

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
	// [×] 注意！！这里千万要只用 malloc 不能用 new ！！因为 new 的话直接就 new T[]，这就会构造 T！！如果 T 的构造函数不是 POD，那么就会编译错误！！
	// [√] 原来如此。由于是就地构造的原因，什么时候构造都可以。可以一开始就开辟内存，但是并不构造～～ 棒！！malloc + replacement new 才是最好的组合哇！
	// 默认的 capacity 是几都可以。反正 size 是 0 就行。多个版本的 STL 中，sgi-stl 默认 capacity 是 0 的。
	// 不过私以为 sgi-stl 的 vector 的构造并不好。因为它并没有用 就地构造 的方法，而是使用了 = 的 拷贝赋值。这样，应该不符合我上边说的第一条了。
	// 有待研究。但是 llvm-stl 库里边，确实是 就地构造 的方法，对于第一条是成立的。所以相对于 llvm 的，我认为 sgi-stl 的构造函数稍稍有些欠缺？研究不透彻，不敢妄言。
	explicit Vector(int capacity = 10/*, const T & t = T()*/) : capacity(capacity), num(0), v((T*)malloc(sizeof(T) * capacity)/*new T[capacity]*/){}	// [×] 不能把 num 上来就设置为 10 ！！！因为如果这时要 push 的话，那岂不是要从 11 个开始吗？	-- size 和 capacity 是不一样的.....这么长时间了这点还是老混。
	Vector(const Vector<T> & v);		// [√] 在 main 函数 返回 Dijkstra distance Vector 的时候，出现 free 两次的情况！！原因是 Vector 进行 copy，是浅拷贝！！这里应该重写拷贝构造函数！！
	void resize(int n);
	void push_back(const T & x);
	T pop_back();
	T & back();
	void print();
	void wprint();
	void rev_print();
	void wrev_print();
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
	this->v = (T*) malloc (sizeof (T) * this->capacity);
	// this->v = new T[capacity];
	for(int i = 0; i < this->num; i ++) {
		// this->v[i] = v.v[i];		// [√] 深拷贝！！！	// [√] 不过这是 “copy construct” 还是 “copy assignment” 啊......是后者。
		// memcpy(&this->v[i], &v.v[i], sizeof(T));		// [√] 虽然符合内存布局，还是可以用 memcpy 拷贝的。但是，这样就是浅拷贝了。对于对象内有 new 的，将会被 free 第二次啊...... 所以不能用 memcpy。
		constructor(&this->v[i], v.v[i]);
	}
}

template <typename T>
void Vector<T>::resize(int n)
{
	T * newbuf = (T*) malloc (sizeof(T) * n);
	// T * newbuf = new T[n];
	for(int i = 0; i < this->num; i ++){
		// newbuf[i] = this->v[i];		// [√]【【【这里的 = 赋值也有问题！！应该在容器的构造中，禁止使用 = 赋值构造！！！】】】
		// memcpy(&newbuf[i], &this->v[i], sizeof(T));		// [×]改成 memcpy 就对了！！
		
		// [√] 应该直接构造。防止对象中的 const & 的情况。
		constructor(&newbuf[i], this->v[i]);
	}
	for(int i = 0; i < this->num; i ++){
		destructor(&this->v[i]);		// 对 replacement new 的析构。
	}
	this->capacity = n;
	free(this->v);
	this->v = newbuf;
}

template <typename T>
void Vector<T>::push_back(const T & x)
{
	if (capacity == 0)	{
		std::cout << "wrong!!" << std::endl;		// 其实，如果要是像 sgi-stl 这样的可以默认 capacity 为 0 的，需要此判断.
		abort();		// 在我们的情况是，shrinked to 0 而引发 bug。现在已解决。
	}
	if(num < capacity){		// 写错成了 <= 导致了 bug......
		// this->v[num++] = x;		// [×]这里的 copy assignment 是本次 Vector 的最大陷阱！！千万不能这么写！！见最上边的说明！要不没法传递 内含 const & 成员的对象！！
								// [×]要改成 memcpy。		// [√]又改回来了。
		constructor(&this->v[num++], x);		// [√] 用 replacement new 就地构造。和 STL 一样了～～
		// std::cout << "copy " << &x << " to " << &this->v[num] << std::endl;	//delete
		// memcpy(&this->v[num++], &x, sizeof(x));
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
		abort();
	}
	T temp = this->v[--num];
	destructor(&this->v[num]);		// replacement delete （逃
	if (capacity > 1 && num <= capacity / 4)	resize (capacity / 2);		// 前边的 capacity > 1 是为了保证 vector 不 shrink 到 capacity 0......注意！！
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

template <typename T>
void Vector<T>::wprint()
{
	std::wcout.imbue(std::locale("zh_CN.UTF-8"));
	for(int i = 0; i < num; i ++){
		std::wcout << v[i] << " ";
	}
	std::wcout << std::endl;
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

template <typename T>
void Vector<T>::wrev_print()
{
	for(int i = num-1; i >= 0; i --){
		std::wcout << v[i] << " ";
	}
	std::wcout << std::endl;
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
	for(int i = 0; i < this->num; i ++) {
		destructor(&this->v[i]);		// replacement new 的析构
	}
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