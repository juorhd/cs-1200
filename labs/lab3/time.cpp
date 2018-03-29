#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <iomanip>
#include <string>
#include "time.h"

using namespace std;

Time::Time(){
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(uintptr_t aHour, uintptr_t aMinute, uintptr_t aSecond){
	hour = aHour;
	minute = aMinute;
	second = aSecond;
}

uintptr_t Time::getHour() const { return hour; }
uintptr_t Time::getMinute() const { return minute; }
uintptr_t Time::getSecond() const { return second; }

void Time::setHour( uintptr_t h ) {
	hour += h;
	while (hour >= 24) hour -= 24;
}
void Time::setMinute ( uintptr_t m ) {
	minute += m; 
	while (minute >= 60) {minute -=60, hour++;
		if (hour == 24) hour = 0;}
}
void Time::setSecond ( uintptr_t s ) {
	second += s; 
	while (second >= 60) {second -= 60, minute++;
		if (minute == 60) {minute=0, hour++;
			if (hour == 24) hour = 0;}}
}

void Time::increment(){
	if ( second == 59 ) {
		second = 0;
		minute++;
		if ( minute == 60 ) {
			minute = 0;
			hour++;
			if ( hour == 24 )
				hour = 0;
		} 
	}
	else second++;
}


void Time::Print_AmPm() const{
	uintptr_t H = hour;
	if ( H > 12 ) H -= 12;

	if ( minute < 10){
		if ( second < 10)  cout << H << ":0" << minute << ":0" << second; 
		else cout << H << ":0" << minute << ':' << second;
	}
	else {
		if ( second < 10)  cout << H << ':' << minute << ":0" << second; 
		else cout << H << ':' << minute << ':' << second; 
	}
	if ( hour == 24 ) cout << "am" << endl;
	else {
	if ( hour == 12 && ( minute || second ) ) cout << "pm" << endl;
	if ( hour > 12 ) cout << "pm" << endl;
	if ( hour == 12 &&  !minute && !second )  cout << "pm" << endl;
	if ( hour < 12 ) cout << "am" << endl;
	}
} 

bool IsEarlierThan ( const Time& t1, const Time& t2){
	if ( t1.getHour() < t2.getHour() ) return true;
	else if ( t1.getHour() == t2.getHour() ){
		if ( t1.getMinute() < t2.getMinute() ) return true;
		else if ( t1.getMinute() == t2.getMinute() ){
			if ( t1.getSecond() < t2.getSecond() ) return true;
		}
	} return false;
}

void change_times (  Time &t1,  Time t2){ //t1 by reference, t2 by value
	t1.setHour ( 1 );
	t1.setMinute (  20 );
	t1.setSecond (  15 );
	
	t2.setHour (  1 );
	t2.setMinute (  20 );
	t2.setSecond (  15 );
}




