#include "BoyerMoore.hh"
#include <cassert>

using namespace std;

int main()
{
	int m = match(L"HERE IS A SAMPLE EXAMPLE", L"EXAMPLE");
	assert(m == 17);

	int mm = match(L"abacadabrabracabracadabrabrabracad", L"abracadabra");
	assert(mm == 14);

	int mmm = match(L"abacadabrabracabracadabrabrabracad", L"bcara");
	assert(mmm == -1);

	int mmmm = match(L"abacadabrabracabracadabrabrabracad", L"rabrabracad");
	assert(mmmm == 23);

	cout << "test Boyer Moore algorithm succeeded!" << endl;
}