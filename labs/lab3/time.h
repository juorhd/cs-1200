


class Time {

public:
	//Constructors
	Time();
	Time(uintptr_t aHour, uintptr_t aMinute, uintptr_t aSecond);

	//Accessories
	uintptr_t getHour() const;
	uintptr_t getMinute() const;
	uintptr_t getSecond() const;

	//Modifiers
	void setHour(uintptr_t aHour);
	void setMinute(uintptr_t aMonth);
	void setSecond(uintptr_t aSecond);
	void increment();

	//other member functions that operate on time objects
	
	void Print_AmPm() const;

private:
	uintptr_t hour;
	uintptr_t minute;
	uintptr_t second;
};
bool IsEarlierThan ( const Time& t1, const Time& t2);
void change_times (  Time &t1,  Time t2);