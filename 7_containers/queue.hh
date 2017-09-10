#ifndef __QUEUE_HH__
#define __QUEUE_HH__

#include <iostream>
#include <cstdlib>

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
	void push_back (const T & elem);
	T & front ();
	void pop_front ();
	void print ();
	int size() const;
	bool empty() const;
	~Queue();
};

template <typename T>
void Queue<T>::push_back (const T & elem)
{
	if (num == capacity - 1){
		std::cout << "buf has been full. You should leave one more empty space." << std::endl;		// 循环队列要余出一个空格
		return;
	}

	*last++ = elem;
	num += 1;
}

template <typename T>
void Queue<T>::pop_front ()
{
	if (num == 0) {
		std::cout << "buf is empty! You can't pop back!" << std::endl;
		return;
	}
	
	first ++;
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
		std::cout << *temp << " ";
	}
	std::cout << std::endl;
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
	free(buf);
}


#endif