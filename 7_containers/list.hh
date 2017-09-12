#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>
#include <functional>

template <typename T>
class List{
public:
	struct Node {
		T elem;
		struct Node *next;
		Node (T elem, struct Node *next) : elem(elem), next(next) {}		// 对内部的 elem，这个初始化列表已经是在 copy construct 了 ！！！
	};
	class Iterator {
	private:
		Node *cur;		
	public:
		explicit Iterator (Node *cur) : cur(cur) {}
		
		/**
		 *	c++ 的 for-each (int i : v) 使用了 Iterator 中的 ++it 前置符， * 操作符解引用（一定要返回 &！！！血和泪啊！！） 还有一个 != 判等符号。应该是用于判定 it != v.end() 的。
		 */

		Iterator operator ++ () 		// for-each 使用了 ++it 这种形式！
		{
			cur = cur->next;
			return *this;
		}

		Iterator operator ++ (int n) 
		{
			Iterator temp = *this;
			cur = cur->next;
			return temp;
		}

		Node * operator -> () 
		{
			return cur;
		}

		T & operator * ()			// 就在这里啊！！！就在这里啊！！！少了一个引用！！弄的我这特别诡异啊！！！ 
						// mdzz......终于。。。发现错误在这里了！！我的 for-each 在我自己的 list 中，每次 (const int & i : list) ，
						// i 的地址居然都是一样的！因为 const & 也可以接收 左值！！！所以，相当于复制了 QAQ......
						// 而，每次结束循环，i 都会出作用域消失掉，因此，每次的 i 都在同一个位置被建立...... 这种 UB 问题已经出现过两遍了！！
		{
			return cur->elem;
		}

		bool operator == (const Iterator & x)
		{
			return this->cur == x.cur;
		}

		bool operator != (const Iterator & x)
		{
			return this->cur != x.cur;
		}

	};
private:
	struct Node *head = nullptr;
	int num = 0;
public:
	List () = default;
	List (const List<T> & list);
	void push_front (const T & elem);
	T pop_front ();
	void print() const;
	void size() const;
	void Delete(const T & t);
	void quick_sort(); 	// http://blog.csdn.net/otuhacker/article/details/10366563
public:
	Iterator iterator() const;
	Iterator begin() const;
	Iterator end() const;
public:
	~List ();
};

template <typename T>
using Node = typename List<T>::Node;

template <typename T>
List<T>::List(const List<T> & list)		// 容器一定要实现 copy construct ！！！！！一·定·要 ！！比如 vector<list<>>，然后两个 vector 拷贝构造，vector 已经实现深拷贝，但是 内部的 list 是浅拷贝，那么终究就还是浅拷贝的，而且 vector 里边用的 destructor，会两个一起析构......QAQ......所以内部的元素，必须是递归的深拷贝的！！！
{
	Node *first = list.head;
	Node *temp_head = nullptr, *temp_rear = nullptr;
	while(first != nullptr) {
		this->num ++;
		temp_rear = new Node(first->elem, nullptr);		// 这个 first->elem 已经是被 copy construct 的了 ！！
		if (temp_head == nullptr){
			temp_head = temp_rear;
			this->head = temp_head;
		} else {
			temp_head->next = temp_rear;
		}
		temp_head = temp_rear;
		first = first->next;
	}
}

template <typename T>
void List<T>::push_front (const T & elem)
{
	this->num ++;
	this->head = new Node(elem, head);
}

template <typename T>
T List<T>::pop_front ()
{
	if(this->num == 0)	std::cout << "no elem in the list but pop!" << std::endl;		// crash
	this->num --;
	Node *temp = head;
	T result = temp->elem;	// copy 一份出来 然后销毁 Node 防止内存泄漏
	head = head->next;
	delete temp;
	return result;
}

template <typename T>
typename List<T>::Iterator List<T>::iterator() const
{
	return Iterator(this->head);
}

template <typename T>
typename List<T>::Iterator List<T>::begin() const
{
	return Iterator(this->head);
}

template <typename T>
typename List<T>::Iterator List<T>::end() const
{
	return Iterator(nullptr);
}

template <typename T>
List<T>::~List()
{
	while(this->head != nullptr){
		Node *temp = head;
		head = head->next;
		delete temp;
	}
}

template <typename T>
void List<T>::print() const
{
	Node *temp = this->head;
	while(temp != nullptr){
		std::cout << temp->elem << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}

template <typename T>
void List<T>::size() const 
{
	return this->num;
}

template <typename T>
void List<T>::Delete(const T & t)
{
	Node **temp = &this->head;
	while (temp && *temp) {	// linus 的删除法。 需要先保证 temp 指针是成立的。
		if ((*temp)->elem == t) {
			Node *del = *temp;
			*temp = (*temp)->next;		// 跳过要被 del 的元素。
			delete del;
			return;
		} else {
			temp = &(*temp)->next;
		}
	}
}

template <typename T>
void List<T>::quick_sort()
{
	auto partition = [this](Node* left, Node* right) -> Node * {
		T sentinel = left->elem;
		Node* first = left;
		Node* second = left->next;
						
		while (second != right) {
													// 默认排好序之后，分割点在中间位置，左边的元素都比他小，右边的元素都比他大。
			if (second->elem < sentinel) {			// 如果右边的元素 *j 小于 分割点哨兵，
				first = first->next;				// 那么左边的指针右移一位。因为它右边的元素肯定比它大。因此把大的换到右边，把小的换到左边。
													// 把右边 *j 的小的元素换到 ++i 这里。
				std::swap(first->elem, second->elem);
				// this->print();
			}
			
			second = second->next;	
		}

		std::swap(first->elem, left->elem);			// 最后把 i 和 哨兵换一下。

		return first;
	};
	std::function<void (Node*, Node*)> real_quick_sort = [&partition, &real_quick_sort, this](Node* left, Node* right) {
		if (left != right) {
			Node* sentinel = partition(left, right);
			// this->print();
			real_quick_sort(left, sentinel);
			real_quick_sort(sentinel->next, nullptr);
		}
	};
	push_front(T{});		// 神奇啊......最前边要加一个 -1......
	real_quick_sort(head, nullptr);	// 本体。
	pop_front();
}


#endif