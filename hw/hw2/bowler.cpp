	#include <iostream>
	#include <cstdlib>
	#include <cstdio>
	#include <vector>
	#include <algorithm>
	#include "bowler.h"

	using namespace std;
	
	//the const string array which could convert int to string
	const string digit[10] = {"0","1","2","3","4","5","6","7","8","9"}; 

	//implementation from bowler.h
	

	//constructor
	
	//takes in inputs and modifies the class
	Bowler::Bowler( string f_name, string l_name, vector<int> scores ){
		Firstname = f_name;
		Lastname = l_name;
		int index = 0;
		for (int i = 1; i <= 10; ++i){
			
			//if it is a strike
			if ( scores[index] == 10 ){
				set_f_val( i, 10 );
				set_f_symbol( i, " " );
				set_s_symbol( i, "X" );
				set_cumulative( i, 10 );
				set_diff( i, 0 );
			}
			
			//otherwise
			if ( scores[index] < 10 ){
				
				//if the hit down num is zero
				if ( scores[index] == 0 ){
					set_f_val( i, 0 );
					set_f_symbol( i, "-" );
				} else { 
					set_f_symbol(i, to_string(scores[index])); 
				}
				
				set_f_val( i, scores[index++] );
				set_s_val( i, scores[index] );
				if ( scores[index] == 0 ){
					set_s_symbol( i, "-" );
				}
				
				//if it is a spare
				else if ( scores[index] + scores[index-1] == 10 ){
					set_s_symbol( i, "/" );
					set_diff( i, 10 - scores[index-1] );
				} else { 
					set_s_symbol(i, to_string(scores[index])); 
					set_diff( i, scores[index] - scores[index-1] );
				}
				set_cumulative( i, get_f_val(i)+get_s_val(i) );
			}
			index++;
		} 
		
		set_cumulative(0, 0);
		
		// special case
		
		// if the second 10th frame is a spare
		if ( is_spare(10) ){
			set_f_val( 11, scores[index] );
			if ( scores[index] == 10 ){ 
				set_f_symbol( 11, "X" );
			} else if ( scores[index] == 0 ) {
				set_f_symbol( 11, "-" );
			} else { set_f_symbol( 11, digit[scores[index]] ); } 
		}
		
		// if the second 10th frame is a strike
		if ( is_strike(10) ){
			set_f_val( 11, scores[index] );
			set_f_symbol( 11, digit[scores[index]] );
			
			// if the 11th throw is a strike
			if ( scores[index] == 10 ){ 
				set_s_symbol( 11, "X" );
				if ( scores[index+1] == 10 ){
					set_s_symbol( 12, "X" );
				} else if ( scores[index+1] == 0 ) {
					set_f_symbol( 12, "-" );
				} else { set_f_symbol( 12, digit[scores[index+1]] ); }
				set_f_val( 12, scores[index+1] );
			} else { 
				index++;
				set_s_val( 11, scores[index] );
				
				if ( scores[index-1] + scores[index] == 10 ){
					set_s_symbol( 11, "/" );
				} else if ( scores[index] == 0 ) {
					set_s_symbol( 11, "-" );
				} else {
					set_s_symbol( 11, digit[scores[index]] );
				} 
				
			}
			
		}
		
		//cumulative score calculation
		
		for (int i = 1; i <= 10; ++i){
			
			//strike case
			if ( is_strike(i) ){
				if ( is_strike(i+1) ){ 
					set_cumulative(i, get_cumulative_score(i) + get_f_val(i+2)+10);
				} else { set_cumulative(i, get_cumulative_score(i) + get_f_val(i+1) + get_s_val(i+1)); }
			}
			//spare case
			if ( is_spare(i) ){
				set_cumulative(i, get_cumulative_score(i) + get_f_val(i+1));
			}
			set_cumulative(i, get_cumulative_score(i) + get_cumulative_score(i-1));
		}
	}

	//sort by name comparator in sort function
	bool sort_by_name ( const Bowler& b1, const Bowler& b2 ){
		if ( b1.get_Lastname() == b2.get_Lastname() ){
			return b1.get_Firstname() < b2.get_Firstname();
		}
		return b1.get_Lastname() < b2.get_Lastname();
	}
	
	//sort by score comparator in sort function
	bool sort_by_score( const Bowler& b1, const Bowler& b2 ){
		if ( b1.get_cumulative_score(10) == b2.get_cumulative_score(10) ){
			if ( b1.get_Lastname() == b2.get_Lastname() ){
				return b1.get_Firstname() < b2.get_Firstname();
			}
			return b1.get_Lastname() < b2.get_Lastname();
		} return b1.get_cumulative_score(10) > b2.get_cumulative_score(10);
	}
	

		