#include "stack.hh"
#include <cassert>

int main()
{
	Stack<int> s;
	s.push(3);
	s.push(4);
	assert (s.top() == 4);
	s.pop();
	assert (s.top() == 3);
	s.pop();
	std::cout << "test stack succeeded!" << std::endl;
}