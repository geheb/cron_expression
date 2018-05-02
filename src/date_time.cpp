#include <stdexcept>
#include <tuple>
#include "date_time.h"

namespace geheb {

date_time date_time::now() {
	auto now = system_clock::now();
	now -= seconds(timezone());
	now -= seconds(daylight_saving_bias());
	return date_time(time_point_cast<seconds>(now));
}

date_time::date_time(const system_clock::time_point &timePoint)
	: _timePoint(time_point_cast<seconds>(timePoint)), _year(0), _month(0), _mday(0), _wday(0), _hour(0), _min(0), _sec(0) {

	const auto timeSinceEpoch = _timePoint.time_since_epoch();
	const auto daysSinceEpoch = duration_cast<days>(timeSinceEpoch);
	_wday = weekday_from_days(daysSinceEpoch);

	std::tie(_year, _month, _mday) = year_month_day_from_days(daysSinceEpoch);
	std::tie(_hour, _min, _sec) = hour_min_sec_from_duration(timeSinceEpoch - daysSinceEpoch);
}

system_clock::time_point date_time::to_time_point(int year, int month, int day, int hour, int min, int sec) const {

	if (year < 1970 || year > 5137) throw std::invalid_argument("year");
	if (month < 1 || month > 12) throw std::invalid_argument("month");
	if (day < 1 || day > 31) throw std::invalid_argument("day");
	if (hour < 0 || hour > 23) throw std::invalid_argument("hour");
	if (min < 0 || min > 59) throw std::invalid_argument("minute");
	if (sec < 0 || sec > 59) throw std::invalid_argument("sec");

	auto time = duration_cast<system_clock::duration>(to_days(year, month, day));
	time += hours(hour);
	time += minutes(min);
	time += seconds(sec);
	return system_clock::time_point(time);
}

// see https://howardhinnant.github.io/date_algorithms.html
std::tuple<int, int, int> date_time::year_month_day_from_days(const days &daysSinceEpoch) const noexcept {
	const auto z = daysSinceEpoch.count() + 719468;
	const auto era = (z >= 0 ? z : z - 146096) / 146097;
	const auto doe = static_cast<unsigned>(z - era * 146097);
	const auto yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
	const auto y = static_cast<days::rep>(yoe) + era * 400;
	const auto doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
	const auto mp = (5 * doy + 2) / 153;
	const auto d = doy - (153 * mp + 2) / 5 + 1;
	const auto m = mp < 10 ? mp + 3 : mp - 9;
	return std::make_tuple(y + (m <= 2), static_cast<int>(m), static_cast<int>(d));
}

std::tuple<int, int, int> date_time::hour_min_sec_from_duration(const system_clock::duration &duration) const noexcept {
	const auto hour = duration_cast<hours>(duration);
	const auto min = duration_cast<minutes>(duration - hour);
	const auto sec = duration_cast<seconds>(duration - hour - min);
	return std::make_tuple(hour.count(), min.count(), static_cast<int>(sec.count()));
}

// see https://howardhinnant.github.io/date_algorithms.html
int date_time::weekday_from_days(const days &daysSinceEpoch) const noexcept {
	const auto z = daysSinceEpoch.count();
	return z >= -4 ? (z + 4) % 7 : (z + 5) % 7 + 6;
}

// see https://howardhinnant.github.io/date_algorithms.html
days date_time::to_days(int year, int month, int day) const noexcept {
	const auto y = static_cast<int>(year) - (month <= 2);
	const auto m = static_cast<unsigned>(month);
	const auto d = static_cast<unsigned>(day);
	const auto era = (y >= 0 ? y : y - 399) / 400;
	const auto yoe = static_cast<unsigned>(y - era * 400);
	const auto doy = (153 * (m > 2 ? m - 3 : m + 9) + 2) / 5 + d - 1;
	const auto doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
	return days(era * 146097 + static_cast<int>(doe) - 719468);
}

long date_time::timezone() noexcept {
	_tzset();
	long value = 0;
	return _get_timezone(&value) == 0 ? value : 0L;
}

long date_time::daylight_saving_bias() noexcept {
	_tzset();
	long value = 0;
	return _get_dstbias(&value) == 0 ? value : 0L;
}

} // namespace geheb
