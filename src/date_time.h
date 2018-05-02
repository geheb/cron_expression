#pragma once
#include <chrono>

namespace geheb {

using namespace std::chrono;
using days = duration<int, std::ratio_multiply<std::ratio<24>, hours::period>>;

class date_time final {
public:
	static date_time now();
	date_time() = delete;
	date_time(const date_time &dt) : date_time(dt._timePoint) {
	}
	date_time(int year, int month, int day, int hour = 0, int minute = 0, int sec = 0)
		: date_time(to_time_point(year, month, day, hour, minute, sec))	{
	}
	date_time(const system_clock::time_point &timePoint);
	operator system_clock::time_point() const noexcept { return _timePoint; }
	operator long long() const noexcept { return _timePoint.time_since_epoch().count(); }
	bool is_leap() const noexcept {
		return _year % 4 == 0 && (_year % 100 != 0 || _year % 400 == 0);
	}
	int last_day_of_month() const noexcept {
		const char lastDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return _month == 2 ? (is_leap() ? 29 : 28) : lastDays[_month - 1];
	}
	int year() const noexcept { return _year; }
	int month() const noexcept { return _month; }
	int day() const noexcept { return _mday; }
	int hour() const noexcept { return _hour; }
	int minute() const noexcept { return _min; }
	int second() const noexcept { return _sec; }
	int day_of_week() const noexcept { return _wday; }
	bool is_weekend() const noexcept { return _wday == 0 || _wday == 6; }
	date_time& operator+=(const system_clock::duration &duration) {
		return *this = date_time(_timePoint + duration);
	}
	date_time operator+(const system_clock::duration &duration) const {
		return date_time(_timePoint + duration);
	}
	date_time& operator-=(const system_clock::duration &duration) {
		return *this = date_time(_timePoint - duration);
	}
	date_time operator-(const system_clock::duration &duration) const {
		return date_time(_timePoint - duration);
	}
	bool operator==(const date_time &dt) const {
		return _timePoint == dt._timePoint;
	}
	bool operator!=(const date_time &dt) const {
		return _timePoint != dt._timePoint;
	}
	bool operator>(const date_time &dt) const {
		return _timePoint > dt._timePoint;
	}
	bool operator>=(const date_time &dt) const {
		return _timePoint >= dt._timePoint;
	}
	bool operator<(const date_time &dt) const {
		return _timePoint < dt._timePoint;
	}
	bool operator<=(const date_time &dt) const {
		return _timePoint <= dt._timePoint;
	}

private:
	static long timezone() noexcept;
	static long daylight_saving_bias() noexcept;

	std::tuple<int, int, int> year_month_day_from_days(const days &daysSinceEpoch) const noexcept;
	std::tuple<int, int, int> hour_min_sec_from_duration(const system_clock::duration &time) const noexcept;
	int weekday_from_days(const days &daysSinceEpoch) const noexcept;
	days to_days(int year, int month, int day) const noexcept;
	system_clock::time_point to_time_point(int year, int month, int day, int hour, int minute, int sec) const;

	system_clock::time_point _timePoint;
	int _year, _month, _mday, _wday, _hour, _min, _sec;

};

} // namespace geheb
