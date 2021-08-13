#ifndef ATORIO_TIME
#define ATORIO_TIME

#include <stdint.h>
#include <string>

class Time {
public:
	Time();
	Time(long long time);
	Time(long long time, long utime);
	virtual ~Time() {}

	void update();
	std::string format(std::string form);
	uint64_t utime() { return unix_utime; }
private:
	uint16_t year;
	uint8_t day, month, hour, minute, second;
	uint32_t micro;

	uint64_t unix_utime;

	void ymdhmsu();
};

#endif
