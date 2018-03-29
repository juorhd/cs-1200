#include <iostream>
#include "time.h"

using namespace std;

Time::Time(){
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(int aHour, int aMinute, int aSecond){
	hour = aHour;
	minute = aMinute;
	second = aSecond;
}

int Time::getHour() const { return hour; }
int Time::getMinute() const { return minute; }
int Time::getSecond() const { return second; }

void Time::setHour( int h ) { hour = h; }
void Time::setMinute ( int m ) { minute = m; }
void Time::setSecond ( int s ) { second = s; }

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


void Time::PrintAmPm() const{
	int H = hour;
	if ( H == 0 ) H = 12;
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





