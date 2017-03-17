#include "union-find.hpp"

void testUnion()
{
	UnionFind uf(10);
	uf.Union(0,3);
	uf.print(); cout << endl;
	uf.Union(4,5);
	uf.Union(1,3);
	uf.Union(1,4);
	uf.print(); cout << endl ;
	uf.find(1);
	cout << uf.connected(1,4)<< endl<< endl;
	uf.print(); cout << endl;
}

int main()
{
	testUnion();
}