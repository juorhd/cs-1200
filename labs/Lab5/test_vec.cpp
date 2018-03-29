#include <iostream>
#include <cmath>
using namespace std;

#include "vec.h"



int main() {

  Vec<int> v100(0, 0);
  v100.push_back(5);
  v100.push_back(5);
  v100.push_back(10);
  remove_matching_elements(v100, 5);
  cout << "Contents of v100:";  
  for ( int i = 0; i < v100.size(); ++i ){
    cout << " " << v100[i];
  } 
  cout << "\n\n\n";

  // ---------------------------------------------------
  // initialize v1 with 10 values...  the multiples of 5
  Vec<int> v1( 10, 0 );
  Vec<int>::size_type i;
  for ( i = 0; i < v1.size(); i++) {
    v1[i] = 5 * i;
  }
  cout << "v1.size() = " << v1.size() << ".  Should be 10.\n";
  cout << "Contents of v1 (multiples of 5):";
  for ( i = 0; i<v1.size(); ++i ) {
    cout << " " << v1[i];
  }
  cout << endl;

  // --------------------------------------------------------------------------
  // make v2 be a copy of v1, but then overwrite the 2nd half with the 1st half
  Vec<int> v2( v1 );
  v2[ 9 ] = v2[ 0 ];
  v2[ 8 ] = v2[ 1 ];
  v2[ 7 ] = v2[ 2 ];
  v2[ 6 ] = v2[ 3 ];
  v2[ 5 ] = v2[ 4 ];
  cout << "Contents of v1 (still multiples of 5):";
  for ( i = 0; i<v1.size(); ++i )
    cout << " " << v1[i];
  cout << endl;
  cout << "Contents of v2 (now palindrome):";
  for ( i = 0; i<v2.size(); ++i )
    cout << " " << v2[i];
  cout << endl;

  remove_matching_elements(v2, 10);
  cout << "Contents of v2 (after remove elements 10):";
  for ( i = 0; i<v2.size(); ++i )
    cout << " " << v2[i];
  cout << endl;

  remove_matching_elements(v2, 5);
  cout << "\nContents of v2 (after remove elements 5):" << endl;
  v2.print();


  // ------------------------------------------
  // make v3 be a copy of v2, but then clear it
  Vec<int> v3;
  v3 = v2;
  v3.clear();
  cout << "\nAfter copying v2 to v3 and clearing v3,  v2.size() = "
       << v2.size() << " and v3.size() = " << v3.size() << endl;
  cout << "Contents of v2 (should be unchanged):";
  for ( i = 0; i<v2.size(); ++i ) {
    cout << " " << v2[i];
  }
  cout << endl;

  // --------------
  // test push back
  cout << "\nNow testing push_back.  Adding 3, 6, 9 to v2:\n";
  v2.push_back( 3 );
  v2.push_back( 6 );
  v2.push_back( 9 );
  cout << "v2 is now: \n";
  for ( i = 0; i<v2.size(); ++i ) {
    cout << " " << v2[i];
  }
  cout << endl;

  // -----------
  // test resize
  v1.resize(20,100);
  cout << "\nNow testing resize.  Resizing v1 to have 20 elements and v2 to have 2 elements\n";
  cout << "v1 is now (should have 100s at the end): \n";
  for ( i = 0; i<v1.size(); ++i )
    cout << " " << v1[i];
  cout << endl;
  v2.resize(2,100);
  cout << "v2 is now: \n";
  for ( i = 0; i<v2.size(); ++i )
    cout << " " << v2[i];
  cout << endl;

  // ------------------------
  // test of a vec of doubles
  cout << "\nStarting from an empty vector, z,  of doubles and doing\n"
       << "5 push_backs\n";
  Vec<double> z;
  for ( i = 0; i<5; ++i )
    z.push_back( sqrt( double(10*(i+1)) ));
  cout << "Contents of vector z: ";
  for ( Vec<double>::size_type j = 0; j < z.size(); j++ )
    cout << " " << z[j];
  cout << endl << endl;



  // ADD MORE TEST CASES HERE
  Vec<int> v4;
  for (int i=0; i<=65; ++i)
    { v4.push_back( i ); v4.print(); cout << endl; }
  for (int i=0; i<=65; ++i)
    { remove_matching_elements(v4, i); v4.print(); cout << endl; }

  Vec<char> v5;
  for (char i='A'; i<='z'; ++i)
    { v5.push_back( i ); v5.print(); cout << endl; }
  for (char i='A'; i<='z'; ++i)
    { remove_matching_elements(v5, i); v5.print(); cout << endl; }

cout<<"v6"<<endl;
  Vec<int> v6;
  for (int i=1; i<=5; ++i) v6.push_back(i);v6.print();
  remove_matching_elements(v6,1); v6.print();
  remove_matching_elements(v6,5); v6.print();

cout<<"v7"<<endl;
  Vec<char> v7;
  for (char i='A'; i<='E'; ++i) v7.push_back(i);v7.print();
  remove_matching_elements(v7,'A'); v7.print();
  remove_matching_elements(v7,'E'); v7.print();

cout<<"v8"<<endl;
  Vec<int> v8;
  v8.push_back(1);v8.print();
  remove_matching_elements(v8, 1); v8.print();
  return 0; 
}
