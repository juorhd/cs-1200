#include <iostream>
#include "vec.h"

using namespace std;
int main(int argc, char *argv[]) {
	int c = 5;
	int& a = c;
	cout << c <<endl << a <<endl;
	c = 10;
	
	cout << c <<endl << a <<endl;
	a = 4;
	cout << c <<endl << a <<endl;

}