#include <iostream>
#include <vector>

void reverse_vector(std::vector <int> &old) {
	int size = old.size();
	int half_size = size / 2;
	for(int i=0; i<half_size; i++) {	
		int tmp = old[i];
		old[i] = old[size-1-i];
		old[size-1-i] = tmp;
	}
}

void printV(std::vector <int> &V) {
	std::cout <<" " << V.size() << std::endl;
	for(int i=0; i<V.size(); i++)
		std::cout << V[i] << ' ';
	std::cout << std::endl;
}

int main() {
	std::vector <int> A;
	for(int i=0; i<1; i++) {
		A.push_back(i*i);			//create a vector of integers
		std::cout << i*i << ' ';	//output the contents
	}
	std::cout<< std::endl;

	reverse_vector(A);				//pass the vector to the reverse function

	printV(A);						//output the resulting vector

	return 0;
}