#include "../list.hh"
#include <cassert>

int main()
{
	List<int> l;
	l.push_front(3);
	l.push_front(4);
	l.push_front(5);
	assert (l.pop_front() == 5);
	assert (l.pop_front() == 4);
	assert (l.pop_front() == 3);
	for(int i : l){			// 迭代器可以使用！！
		std::cout << i << " ";
	}

	l.push_front(1);
	l.push_front(5);
	l.push_front(3);
	l.push_front(8);
	l.push_front(9);
	l.push_front(0);
	l.Delete(8);
	l.Delete(5);
	l.quick_sort();
	// for(int i : l) {
	// 	std::cout << i << " ";
	// }

	// List<int> ll(l);
	// for(int i : ll) {
	// 	std::cout << i <<" ";
	// }

	std::cout << "test list succeeded!" << std::endl;
}