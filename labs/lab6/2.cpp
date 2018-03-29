#include <iostream>
#include <vector>
#include <cassert>
#include <list>
using namespace std;
typedef unsigned int uint;

template <class T> void reverse_vector(std::vector<T>& v)
{
	for (uint i=0; i<(v.size()/2); i++)
	{
		T swap;
		swap = v[i];
		v[i] = v[v.size()-1-i];
		v[v.size()-1-i] = swap;
	}
}

template <class T> void print_v(std::vector<T>& v)
{
	for (uint i=0; i<v.size(); i++)
		cout << v[i] <<" ";
	cout <<endl;
}

void test_vector(uint v_size)
{	
	std::vector<int> expc;
	std::vector<int> v;
	cout << "Vector Test case Size: ";
	for(uint i=0; i<v_size; i++) v.push_back(i+1);
	cout << v.size() <<endl;
	cout << "Contents: ";
	print_v(v);
	for(uint i=v_size; i>0; i--) expc.push_back(i);
	reverse_vector(v);
	assert(v==expc);
	cout << "Test successed." <<endl;
	cout << "Expected Out: ";
	print_v(v);
	cout <<endl;
}

template <class T> void reverse_list(list<T>& l)
{
	typename list<T>::reverse_iterator ri;
	uint counter = 0;
	typename list<T>::iterator i;
	i = l.begin();

	for(ri = l.rbegin(); ri!=l.rend(); ri++)
	{
		if (counter == l.size()/2) break;
		counter++;
		T swap;
		swap = *ri;
		*ri = *i;
		*i = swap;
		i++;
	}
}

template <class T> void print_l(list<T>& l)
{
	typename list<T>::iterator i;
	for(i=l.begin(); i!=l.end(); i++)
		cout << *i << " ";
	cout <<endl;
}

void test_list(uint l_size)
{
	list<int>::reverse_iterator ri;
	list<int> expc;
	list<int> a;
	cout << "List Test case Size: ";
	for (uint i=0; i<l_size; i++) a.push_back(i*i);
	cout << a.size() <<endl;
	cout << "Contents: ";
	print_l(a);

	for( ri = a.rbegin(); ri != a.rend(); ++ri ) expc.push_back(*ri);
	reverse_list(a);
	assert(a==expc);
	cout << "Test Successed." <<endl;
	cout << "Reversed Version: ";
	print_l(a);
	cout <<endl;
}

int main(int argc, char const *argv[])
{	
	uint n = 9;
	test_vector(n);
	n = 4;
	test_vector(n);
	n = 1;
	test_vector(n);
	n = 0;
	test_vector(n);
	
	n = 9;
	test_list(n);
	n = 4;
	test_list(n);
	n = 1;
	test_list(n);
	n = 0;
	test_list(n);
	
	return 0;
}