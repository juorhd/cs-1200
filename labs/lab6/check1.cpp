#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void reverse_vec( vector<int>& v ){
	if ( v.size() == 0 )
		return;
	else{
		for ( int i = 0; i < v.size()/2; ++i )
			swap( v[i], v[v.size()-1-i] );
	}
}

void print( const vector<int>& v ){
	for ( int i = 0; i < v.size(); ++i ){
		cout << v[i] << ' ';
	}
	cout << endl;
}

int main() {
	vector<int> v1;
	
	v1.push_back(7);
	v1.push_back(3);
	v1.push_back(2);
	v1.push_back(1);
	v1.push_back(9);
	v1.push_back(10);
	
	print(v1);
	reverse_vec(v1);
	print(v1);

}