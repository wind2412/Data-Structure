#include "vector.hh"
#include <cassert>

int main()
{
	Vector<int> v(3);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	assert (v[0] == 3);
	assert (v[1] == 4);
	assert (v[2] == 5);
	assert (v[3] == 6);
	assert (v[4] == 7);
	int n = 3;
	for(Vector<int>::Iterator it = v.begin(); it != v.end(); it ++){
		assert(n++ == *it);
	}
	v.pop_back();
	n = 3;
	for(int i : v){
		assert(i == n++);
	}
	v.pop_back();
	v.pop_back();
	v.pop_back();
	v.pop_back();
	std::cout << "test vector succeeded!" << std::endl;
}