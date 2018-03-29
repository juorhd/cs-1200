#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bowler.h"

using namespace std;

//the const string array which could convert int to string
const string improvement[10] = {"0","+1","+2","+3","+4","+5","+6","+7","+8","+9"}; 

//read function takes in the data
int read_data( ifstream& fin, vector<Bowler>& participants){
	string f_name, l_name;
	string score;
	vector<int> scores;
	int max_length = 0;
	
	fin >> f_name;
	
	//store data and calculate the max_name_length
	while (fin >> l_name){
		scores.clear();
		while ( fin >> score && isdigit(score[0]) )
			scores.push_back( stoi(score) );
		Bowler individual(f_name, l_name, scores);
		participants.push_back(individual);
		if ( f_name.length()+l_name.length() > max_length )
			max_length = f_name.length()+l_name.length();
		f_name = score;
	}
	return max_length;
}

//print data function takes in data and max name length
//prints the table we want
void print_data( ofstream& fout, vector<Bowler>& participants, int name_width){
	fout << string(name_width+67,'-') << endl;
	
	//print the first row of every bowler
	for (int i=0; i<participants.size(); ++i){
		fout << "| ";
		fout.width(name_width+1);
		fout << left << participants[i].get_Firstname() 
		     + ' ' + participants[i].get_Lastname() << " |";
		for (int j=1; j<=9; ++j){
			fout << ' ' << participants[i].get_f_symbol(j) << ' '
			     << participants[i].get_s_symbol(j) << " |";
		} 
		
		//if that person achieve strike at 10th frame
		if ( participants[i].is_strike(10) ){
			if ( participants[i].get_f_val(11) == 10 ){
				if ( participants[i].get_f_val(12) == 10 )
					fout << " X X X |";
				else { fout << " X X " + participants[i].get_f_symbol(12) + " |"; }
			} else { fout << " X " + participants[i].get_f_symbol(11) + " "
					       + participants[i].get_s_symbol(11) + " |" ;
			}
			
		//if that person achieve spare at 10th frame
		} else if ( participants[i].is_spare(10) ){
			fout << " " + participants[i].get_f_symbol(10) + " / "
				    + participants[i].get_f_symbol(11) +" |" ;
				
		//otherwise
		} else {
			fout << " " + participants[i].get_f_symbol(10) + " "
		                    + participants[i].get_s_symbol(10) + "   |" ;
		}
		fout << endl << "|" + string(name_width+3, ' ') + "|";
		for (int j=1; j<=10; ++j){
			fout << " ";
			fout.width(3);
			if ( j == 10 ) fout.width(5);
			fout << right << participants[i].get_cumulative_score(j) << " |";

		}
		fout << endl << string(name_width+67,'-') << endl;	
	} fout << endl;
}


//standard print function
void print_by_score( ofstream& fout, vector<Bowler>& participants, int name_width ){
	for ( int i = 0; i < participants.size(); ++i ){
		fout.width(name_width+3);
		fout << left << participants[i].get_Firstname()+' '
			        +participants[i].get_Lastname();
		
		fout.width(3);
		fout << right << participants[i].get_cumulative_score(10) << endl;
	}
}

//custom print function
void print_by_diff( ofstream& fout, vector<Bowler>& participants, int name_width){
	fout << endl << "CUSTOM TABLE: THOSE WHO IMPROVE!" << endl;
	fout << string(name_width+67,'-') << endl;
	
	//print the first row of every bowler
	for (int i=0; i<participants.size(); ++i){
		
		int sum = 0;
		for (int j = 1; j <= 10; ++j ){
			if ( participants[i].get_diff(j) >= 2 )
			sum ++;
		}
		if ( sum < 4 ) continue;
		
		
		fout << "| ";
		fout.width(name_width+1);
		fout << left << participants[i].get_Firstname() 
		     + ' ' + participants[i].get_Lastname() << " |";
		for (int j=1; j<=9; ++j){
			fout << ' ' << participants[i].get_f_symbol(j) << ' '
			     << participants[i].get_s_symbol(j) << " |";
		} 
		
		//if that person achieve strike at 10th frame
		if ( participants[i].is_strike(10) ){
			if ( participants[i].get_f_val(11) == 10 ){
				if ( participants[i].get_f_val(12) == 10 )
					fout << " X X X |";
				else { fout << " X X " + participants[i].get_f_symbol(12) + " |"; }
			} else { fout << " X " + participants[i].get_f_symbol(11) + " "
					       + participants[i].get_s_symbol(11) + " |" ;
			}
			
		//if that person achieve spare at 10th frame
		} else if ( participants[i].is_spare(10) ){
			fout << " " + participants[i].get_f_symbol(10) + " / "
				    + participants[i].get_f_symbol(11) +" |" ;
				
		//otherwise
		} else {
			fout << " " + participants[i].get_f_symbol(10) + " "
		                    + participants[i].get_s_symbol(10) + "   |" ;
		}
		fout << endl << "|" + string(name_width+3, ' ') + "|";
		for (int j=1; j<=10; ++j){
			fout << " ";
			fout.width(3);
			if ( j == 10 ) fout.width(5);
			if ( participants[i].get_diff(j) > 0 )
				fout << right << improvement[participants[i].get_diff(j)] << " |";
			else fout << right << participants[i].get_diff(j) << " |";

		}
		fout << endl << string(name_width+67,'-') << endl;	
	}
}


int main(int argc, char *argv[]) {
	//open file and check
	ifstream fin(argv[1]);
	if(!fin.good()){
		cerr<<"Can't open "<<argv[1]<<" to read.\n";
		exit(1);
	} 
	//creat file to write
	ofstream fout(argv[2]);
	if(!fout.good()){
		cerr<<"Can't open "<<argv[2]<<" to read.\n";
	}
	string command = argv[3];
	
	vector<Bowler> participants;
	int name_width = read_data( fin, participants );
	sort( participants.begin(), participants.end(), sort_by_name );
	print_data( fout, participants, name_width );
	
	if ( command == "standard" ){
		sort( participants.begin(), participants.end(), sort_by_score );
		print_by_score(fout, participants, name_width);
	}
	
	if ( command == "custom" ){
		print_by_diff( fout, participants, name_width );
	}
}