在编写容器 Vector 的时候，绝对不能用 copy assignment 去对 malloc 的野内存进行赋值。
这种情况一般发生在 push_back 和 resize 的实现上。
比如这种类：

```cpp
class Car {
private:
	std::wstring license;
	const Timer & timer;		// 错误的发生地！！！
	long time;
private:
	static std::wstring make_license();
public:
	Car (const Timer & timer) : timer(timer), time(timer.get_minute()), license(make_license()) {}
	// 拷贝构造没问题。因为 timer 这个引用会被初始化。
	// 不过拷贝赋值有问题。因为 car1 = car2 中，timer 本来声明的是 const，但是却被 car2 赋值而变化了...... 虽然 这两个timer 本来就是一个......
	// 所以拷贝赋值如果不自己写一个，就会报错的。因为 const & 不允许再赋值。
	// Car & operator = (const Car & car);
public: 
	long getArriveTime();
	std::wstring getLicense();
	long get_cost();
};
```

看我的注释就能看出来，错误发生在 const & 的那个 timer 成员上。

```cpp
// 首先。1. 正常的 vector<Car> vv(10) 会默认构造 10 个 真的对象 car 出来。因此，如果 car 没有默认的构造函数，那么就会出错的。因为并不知道默认的参数。
// 其次。2. 我自己的 Vector 在 push_back Car 的时候有问题。因为我的 push_back 默认是用 = 号 赋值的。Vector 中，push_back(const T & x) { *this->v++ = x; } 这样赋值的。所以在我的 Car 这里就会出错！
// 		   因为 Car 内部有一个 const & ！！而 如果是赋值的话 *this->v++ = x，成员 const & 是没法赋值的！！因为已经是 const 了。常引用无法改变引用的对象啊！！所以编译器会提示 默认的 copy assignment 已经被 delete 了 ！！！
//		   但是，真正的 STL vector 没有这个限制啊！！这么写是对的！！我需要查看一下 STL 的源代码。  
// 		-- 更新 2017.9.10  查到了。STL 源码是调用分配器 allocator，直接在 *this->v++ 上【就地构造】的！！也对。我的设计用赋值确实是有问题的。其实我也发现这个问题了。因为一开始 *this->v 的地方是野的。原先那里只是被 malloc 了，
//		   空有内存但是没有对象，又怎么能被另一个对象给“拷贝赋值”呢？只有两边都是对象，才可以“拷贝赋值”吧！而我现在的状况，则是左手边空有内存，而是强制让 C++ 把这一坨内存看成了一个对象。这样根本就不符合“拷贝赋值”的语义的。
//		   没有办法......毕竟还没有写那种内存池的能力。 等学了 STL 之后一定要重新写一个 Vector。
//		   目前，想到了两个解决办法。
//		   一个解决办法就是强制把 Car 里边成员变量的 const & 去掉......但是这样太恶心了！[——我的 Vector 竟然不能接受含有 const & 成员的对象！！]说出去丢人......TAT！！
//		   还有另一个解决办法，就是改 Vector 的源码，强行在 push_back 的时候，不使用 = 复制构造，而是强制使用 memset 来拷贝内存。这样也可以达到目的，而且能够达到某种程度模仿 allocator 的效果。
//		   就选第二种了 QAQ
```
