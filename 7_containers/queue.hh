#ifndef __QUEUE_HH__
#define __QUEUE_HH__

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "vector.hh"		// 虽然并没有用到 vector，但是还是使用了 它内部的 constructor 和 destructor。
// 详见 Vector.hh，关于传递内部含有 const & 成员的对象会编译错误的 bug！！！

template <typename T>
class Queue {
private:
	int capacity;
	int num = 0;
	T *buf;
	T *first;
	T *last;
public:
	Queue (int capacity = 10) : capacity(capacity), buf((T*) malloc (sizeof(T) * capacity)), first(buf), last(buf) {}
	Queue (const Queue & q);		// 防止像 Vector 一样，两个 Queue 进行拷贝构造的时候由于浅拷贝出现的问题。因为 buf 是要进行 malloc 的。
	void push_back (const T & elem);
	T & front ();
	void pop_front ();
	void print ();
	void wprint ();
	int size() const;
	bool empty() const;
	~Queue();
};

template <typename T>
Queue<T>::Queue(const Queue<T> & q)		// 未检查错误。
{
	this->capacity = q.capacity;
	this->num = q.num;
	this->buf = (T*) malloc (sizeof(T) * capacity);
	this->first = q.first - q.buf + this->buf;
	this->last = q.last - q.buf + this->buf;
	T * temp = this->first;
	T * temp2 = q.first;
	while(temp != this->last) {
		// memcpy(temp, temp2, sizeof(T));
		constructor(temp, *temp2);
		temp ++;
		temp2 ++;
		if (temp == buf + capacity) temp -= capacity;
		if (temp2 == q.buf + q.capacity) temp2 -= q.capacity;
	}

}

template <typename T>
void Queue<T>::push_back (const T & elem)
{
	if (num == capacity - 1){
		std::cout << "buf has been full. You should leave one more empty space." << std::endl;		// 循环队列要余出一个空格
		return;
	}

	// *last++ = elem;		// 见最上方对此 bug 的说明。
	// 要改成 memcpy。
	// memcpy(last, &elem, sizeof(elem));		// [×]成功。
	constructor(last, elem);
	if (++last >= buf + capacity) {
		last -= capacity;
	}

	// std::wcout.imbue(std::locale("zh_CN.UTF-8"));
	// std::wcout << " elem is ..." << elem << std::endl;		// print

	num += 1;
}

template <typename T>
void Queue<T>::pop_front ()
{
	if (num == 0) {
		std::cout << "buf is empty! You can't pop back!" << std::endl;
		return;
	}
	
	destructor(first);
	if (++first >= buf + capacity) {
		first -= capacity;
	}
	num -= 1;
}

template <typename T>
T & Queue<T>::front ()
{
	if (num == 0) {
		std::cout << "buf is empty! You can't pop back!" << std::endl;
		abort();			// 直接崩溃。
	}
	return *first;	
}

template <typename T>
void Queue<T>::print ()
{
	for(T *temp = first; temp != last; temp ++) {
		if (temp == buf + capacity) {
			temp = buf;			// 如果 temp 越界的话， 那么把 temp 归零。
			if (temp == last)	break;
		}
		std::cout << *temp << " ";
	}
	std::cout << std::endl;
}

template <typename T>
void Queue<T>::wprint ()
{
	for(T *temp = first; temp != last; temp ++) {
		if (temp == buf + capacity) {
			temp = buf;			// 如果 temp 越界的话， 那么把 temp 归零。
			if (temp == last)	break;
		}
		std::wcout << *temp << " ";
	}
	std::wcout << std::endl;
}

template <typename T>
int Queue<T>::size() const
{
	return this->num;
}

template <typename T>
bool Queue<T>::empty() const
{
	return this->num == 0;
}

template <typename T>
Queue<T>::~Queue ()
{
	while(first != last) {
		if (first > buf + capacity){
			first = buf;
			continue;
		}
		first->~T();
		first ++;
	}
	free(buf);
}


#endif