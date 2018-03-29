#include <iostream>

using namespace std;

void searchpath(int x, int y, int &solution){
	if ( x == 0 && y == 0)  { solution++; return; }
	if ( x == 0 ) return searchpath(x, y-1, solution);
	if ( y == 0 ) return searchpath(x-1, y, solution);
	searchpath(x, y-1, solution);
	searchpath(x-1, y, solution);
}

int main(){
	int x,y;
	cin >> x >> y;
	int solution=0;
	searchpath(x, y, solution);
	cout << solution << endl;
	return 0;
}