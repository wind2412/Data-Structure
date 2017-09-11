#ifndef __STACK_HH__
#define __STACK_HH__

#include "vector.hh"

template <typename T>
class Stack {
private:
	Vector<T> v;
public:
	void push (const T & e);
	T & top ();
	void pop ();
	bool empty();
	int size();
	void print();
	void wprint();
};

template <typename T>
void Stack<T>::push (const T & e)
{
	v.push_back(e);
}

template <typename T>
T & Stack<T>::top ()
{
	return v.back();
}

template <typename T>
void Stack<T>::pop ()
{
	v.pop_back();
}

template <typename T>
int Stack<T>::size ()
{
	return v.size();
}

template <typename T>
bool Stack<T>::empty ()
{
	return v.size() == 0;
}

template <typename T>
void Stack<T>::print ()
{
	v.rev_print();
}

template <typename T>
void Stack<T>::wprint ()
{
	v.wrev_print();
}

#endif