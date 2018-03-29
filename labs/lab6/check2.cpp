#include <iostream>
#include <cmath>
#include <list>

using namespace std;

void reverse_list( list<int>& v ){
	if ( v.size() == 0 )
		return;
	else{
		list<int>::iterator i = v.begin();
		list<int>::reverse_iterator j = v.rbegin();
		
		for ( int k = 0; k < v.size()/2; ++i, ++j, ++k )
			swap( *i, *j );
	}
}

void print( list<int>& v ){
	for ( list<int>::iterator i = v.begin(); i != v.end(); ++i ){
		cout << *i << ' ';
	}
	cout << endl;
}

int main() {
	list<int> l1;
	
	l1.push_back(7);
	l1.push_back(3);
	l1.push_back(2);
	l1.push_back(1);
	l1.push_back(9);
	l1.push_back(10);
	
	print(l1);
	reverse_list(l1);
	print(l1);

}