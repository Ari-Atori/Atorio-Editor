#include <stdint.h>
#include "Time.hpp"

#include <chrono>

Time::Time() {
	using time_stamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>;
	time_stamp ts = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
	unix_utime = ts.time_since_epoch().count();
	ymdhmsu();
}

Time::Time(long long time) {
	unix_utime = time * 1000000;
	ymdhmsu();
}

Time::Time(long long time, long utime) {
	unix_utime = time * 1000000 + utime;
	ymdhmsu();
}

void Time::update() {
		using time_stamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>;
		time_stamp ts = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
		unix_utime = ts.time_since_epoch().count();
		ymdhmsu();
}

std::string Time::format(std::string form) {
	return std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year);
}

static int getYear(uint64_t* days) {
	int year = 1900;
	*days += 25567;
	int leap = 0;
	while (*days >= (uint64_t) (36524ULL + leap)) {
		*days -= (uint8_t) (36524ULL + leap);
		year += 100;
		leap =  ((year % 100) || !(year % 400)) ? 1 : 0;
	}
	while (*days >= (uint64_t) (365ULL + leap)) {
		*days -= (365ULL + leap);
		year++;
		leap =  (!(year % 4)) ? 1 : 0;
	}
	return year;
}

static int getMonth(uint64_t* days, int year) {
	int month = 0;
	unsigned int daysinmonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (!(year % 4) && ((year % 100) || !(year % 400)))
		daysinmonth[1] = 29;
	while (*days >= daysinmonth[month])
		*days -= daysinmonth[month++];
	return month + 1;
}

void Time::ymdhmsu() {
	uint64_t tmp = unix_utime;

	micro = (tmp % 1000000); tmp /= 1000000;
	second = (tmp % 60); tmp /= 60;
	minute = (tmp % 60); tmp /= 60;
	hour = (tmp % 24); tmp /= 24;


	year = getYear(&tmp);
	month = getMonth(&tmp, year);
	day = (uint8_t) (tmp + 1);
}
