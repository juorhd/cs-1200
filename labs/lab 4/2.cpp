#include <iostream>
using namespace std;

void compute_squares(uintptr_t a[], uintptr_t b[], const uintptr_t &size) {
	for (uintptr_t i = 0; i < size; i++)
		*(b+i) = *(a+i) * *(a+i);
}

int main() {
  cout << "size of uintptr_t: " << sizeof(uintptr_t) << endl;
	
  uintptr_t a[4] = {1, 3, 5, 6};
	uintptr_t b[3];
	
  label_stack(&a[0],"a[0]");
  label_stack(&a[1],"a[1]");
  label_stack(&a[2],"a[2]");
  //label_stack(&a[3],"a[3]");
  label_stack(&b[0],"b[0]");
  label_stack(&b[1],"b[1]");
  label_stack(&b[2],"b[2]");

  print_stack();
  compute_squares(a, b, 4);
  print_stack();

	return 0;
}