#include <iostream>
#include <list>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;


void print(const std::string &label, const std::list<std::string> &data) {
	std::cout << label;
	for (std::list<std::string>::const_iterator itr = data.begin();
			 itr != data.end(); itr++) {
		std::cout << " " << *itr;
	}
	std::cout << std::endl;
}

void update( list<string> &data, const vector<string>& add, const vector<string>& remove ){
	
	bool found;
	
	for ( int i = 0; i < add.size(); ++i ){
		found = false;
			
		if ( find(data.begin(), data.end(), add[i]) != data.end() ) continue;		
				
		for ( list<string>::iterator j = data.begin(); j != data.end(); ++j ){
			
			if ( add[i] < *j ){
				data.insert( j, add[i] );
				found = true;
				break;
			}
		}
		if ( !found ) data.push_back(add[i]);
	}
	for ( int i = 0; i < remove.size(); ++i ){
		for ( list<string>::iterator j = data.begin(); j != data.end(); ){
			if ( (*j).find( remove[i] ) != string::npos ){
				j = data.erase( j );
				continue;
			}
			++j;
		}
	}
}


int main() {


	// Examples demonstrating STL string find:
	// catfish contains the substring fish
	assert (std::string("catfish").find(std::string("fish")) != std::string::npos);
	// fish contains the substring fish
	assert (std::string("fish").find(std::string("fish")) != std::string::npos);
	// fish does not contain the substring catfish
	assert (std::string("fish").find(std::string("catfish")) == std::string::npos);


	// A simple example:
	std::list<std::string> data;
	data.push_back("antelope");
	data.push_back("catfish");
	data.push_back("giraffe");
	data.push_back("llama");
	data.push_back("jellyfish");
	data.push_back("whale_shark");
	data.push_back("zebra");

	std::vector<std::string> add;
	add.push_back("tiger");
	add.push_back("aaa");
	add.push_back("llama");
	add.push_back("elephant");
	add.push_back("zzz");

	
	std::vector<std::string> remove;
	remove.push_back("fish");
	remove.push_back("bear");
	remove.push_back("whale");
	remove.push_back("a");
	
	print ("before:",data);
	update(data,add,remove);
	print ("after: ",data);
	
	// at the end, data should contain: antelope elephant giraffe llama tiger zebra
	//assert (data.size() == 6);

}

