class Time {
public:
	Time();
	Time(uintptr_t aHour, uintptr_t aMinute, uintptr_t aSecond);

	uintptr_t getHour() const;
	uintptr_t getMinute() const;
	uintptr_t getSecond() const;

	void setHour (uintptr_t aHour);
	void setMinute (uintptr_t aMinute);
	void setSecond (uintptr_t aSecond);
	void print () const;

private:
	uintptr_t hour;
	uintptr_t minute;
	uintptr_t second;
};