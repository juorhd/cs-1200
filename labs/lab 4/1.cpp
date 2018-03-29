#include <iostream>
using namespace std;

void compute_squares(unsigned int* a, unsigned int* b, const unsigned int &size) {
	for (unsigned int i = 0; i < size; i++)
		*(b+i) = *(a+i) * *(a+i);
}

int main() {
	const unsigned int n = 10;
	unsigned int a[n], b[n];
	for (unsigned int i = 0; i < n; i++)
		cin >> *(a+i);
	compute_squares(a, b, n);
	for (unsigned int i = 0; i < n; i++)
		cout << *(b+i) << ' ';
	cout << endl;

	return 0;
}