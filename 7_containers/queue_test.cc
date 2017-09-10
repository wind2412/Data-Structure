#include "queue.hh"
#include <iostream>
#include <cassert>

int main()
{
	Queue<int> q(3);
	q.push_back(1);
	q.push_back(3);
	assert (q.front() == 1);
	q.pop_front();
	assert (q.front() == 3);
	q.pop_front();
	std::cout << "test queue succeeded!" << std::endl;
}