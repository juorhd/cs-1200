


class Time {

public:
	//Constructors
	Time();
	Time(int aHour, int aMinute, int aSecond);

	//Accessories
	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	//Modifiers
	void setHour(int aHour);
	void setMinute(int aMonth);
	void setSecond(int aSecond);
	void increment();

	//other member functions that operate on time objects
	
	void PrintAmPm() const;

private:
	int hour;
	int minute;
	int second;
};
bool IsEarlierThan ( const Time& t1, const Time& t2);