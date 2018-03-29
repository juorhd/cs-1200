#ifndef __bowler_h_
#define __bowler_h_

using namespace std;

class Bowler{
	
public:
	struct Score{
		int first;
		int second;
		int cumulative;
		int diff;
		
		string f_symbol;
		string s_symbol;
	};
	
//Defalult constructor
	Bowler();
	Bowler(string f_name, string l_name, vector<int> scores);

		
//accessor
		
	//take in frame index number
	//get value of first throw of that frame
	int get_f_val( int index ) const{ return frame[index].first; }
		
	//take in frame index number
	//get value of second throw of that frame
	int get_s_val( int index ) const{ return frame[index].second; }
	
	//take in frame index number
	//get value of difference between first throw and second throw of that frame
	int get_diff( int index ) const{ return frame[index].diff; }	
	
	//take in frame index number
	//get value of the cumulative score of that frame
	int get_cumulative_score( int index ) const{ return frame[index].cumulative; }

	//return string of that person's first name
	const string& get_Firstname() const{ return Firstname; }
		
	//return string of that person's last name
	const string& get_Lastname() const{ return Lastname; }
		
	//take in frame index number
	//get symbol of first throw of that frame
	const string& get_f_symbol( int index ) const { return frame[index].f_symbol; }
	
	//take in frame index number
	//get symbol of second throw of that frame
	const string& get_s_symbol( int index ) const { return frame[index].s_symbol; }
		
		
//modifier
		
	//take in frame index number
	//set the symbol of first throw appear on the board
	void set_f_symbol( int index, string str ){ frame[index].f_symbol = str; }
		
	//take in frame index number
	//set the symbol of second throw appear on the board
	void set_s_symbol( int index, string str ){ frame[index].s_symbol = str; }
		
	//take in frame index number 
	//set the value of first throw appear on the board
	void set_f_val( int index, int val ){ frame[index].first = val; }
		
	//take in frame index number
	//set the value of second throw appear on the board
	void set_s_val( int index, int val ){ frame[index].second = val; }
		
	//take in frame index number 
	//set the value of the score of that frame
	void set_cumulative( int index, int val ){ frame[index].cumulative = val; }
	
	//take in frame index number 
	//set the value of the difference of first and second throw of that frame
	void set_diff( int index, int val ){ frame[index].diff = val; }


		
		
//other helper functions
		
	//take in frame index number
	//determine whether the bowler acheives a strike
	bool is_strike(int index) const{ return get_s_symbol(index) == "X" ; }
	
	//take in frame index number
	//determine whether the bowler acheives a spare
	bool is_spare(int index) const{ return get_s_symbol(index) == "/"  ; }
		
		
		

	
private:
	string Firstname, Lastname;
	Score frame[13];
	
};
bool sort_by_name ( const Bowler& b1, const Bowler& b2);
bool sort_by_score ( const Bowler& b1, const Bowler& b2);


#endif