#include <iomanip>
#include <iostream>
#include "time.h"
#include "print_stack.cpp"
using namespace std;

Time::Time() {
	second = 0;
	minute = 0;
	hour = 0;
}

Time::Time(uintptr_t aHour, uintptr_t aMinute, uintptr_t aSecond) {
	second = aSecond;
	minute = aMinute;
	hour = aHour;
}

uintptr_t Time::getHour() const { return hour; }

uintptr_t Time::getMinute() const { return minute; }

uintptr_t Time::getSecond() const { return second; }

void Time::setHour(uintptr_t h) { hour = h; }

void Time::setMinute(uintptr_t m) { minute = m; }

void Time::setSecond(uintptr_t s) { second = s; }



void change_times(Time &t1, Time t2) {
	label_stack((uintptr_t*)&t1,"t1_func");
	label_stack((uintptr_t*)&t2,"t2_copy");
	print_stack();

	t1.setHour(t1.getHour() + 1);
	t1.setMinute(t1.getMinute() + 30);
	t2.setHour(t2.getHour() + 1);
	t2.setMinute(t2.getMinute() + 30);
}

int main() {
	cout << "size of uintptr_t(Time): " << sizeof(Time) << endl;

	Time t1(3, 4, 5);
	Time t2(12, 13, 14); 

  	label_stack((uintptr_t*)&t1,"t1");
  	label_stack((uintptr_t*)&t2,"t2");
	print_stack();
	
	change_times(t1, t2);
	
	//label_stack((uintptr_t*)&t1,"t1");
  	//label_stack((uintptr_t*)&t2,"t2");
	print_stack();


	return 0;
}