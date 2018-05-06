#include "day_of_week_field.h"

namespace geheb {

day_of_week_field::day_of_week_field() {
	_allowBackwardRange = true;
	_literals =	{
		{ "SUN", 0 },
		{ "MON", 1 },
		{ "TUE", 2 },
		{ "WED", 3 },
		{ "THU", 4 },
		{ "FRI", 5 },
		{ "SAT", 6 }
	};
}

bool day_of_week_field::validate(const std::string &value) const {
	if (value == "?") return true;
	std::string lastDayOfWeek = parse_last_day_of_week(value);
	if (!lastDayOfWeek.empty()) {
		return cron_field::validate(lastDayOfWeek);
	}
	auto nthDayOfWeek = parse_nth_day_of_week(value);
	if (nthDayOfWeek.has_values()) {
		if (!cron_field::validate(nthDayOfWeek.day)) return false;
		int count = std::stoi(nthDayOfWeek.count);
		return count >= 1 && count <= 5;
	}
	return cron_field::validate(value);
}

bool day_of_week_field::match(const std::string &value, const date_time &time) const {
	if (value == "?") return true;
	// allows to specify constructs such as "the last Friday" 5L of a given month
	std::string lastDayOfWeek = parse_last_day_of_week(value);
	if (!lastDayOfWeek.empty()) {
		int targetDayOfWeek = std::stoi(lastDayOfWeek);
		date_time targetTime(time.year(), time.month(), time.last_day_of_month());
		while (targetTime.day_of_week() != targetDayOfWeek) {
			targetTime -= days(1);
		}
		return time.day() == targetTime.day();
	}
	// allows to specify constructs such as "the second Friday" 5#2 of a given month
	auto nthDayOfWeek = parse_nth_day_of_week(value);
	if (nthDayOfWeek.has_values()) {
		int targetDay = std::stoi(nthDayOfWeek.day);
		int targetDayCount = std::stoi(nthDayOfWeek.count);
		// current day of week must match the targeted day of week
		if (time.day_of_week() != targetDay) return false;
		date_time targetTime(time.year(), time.month(), 1);
		int lastDayOfMonth = targetTime.last_day_of_month();
		int count = 0;
		do {
			if (targetTime.day_of_week() == targetDay && ++count >= targetDayCount) break;
			targetTime += days(1);
		} while (targetTime.day() < lastDayOfMonth + 1);
		return time.day() == targetTime.day();
	}
	return cron_field::match(value, time.day_of_week());
}

date_time day_of_week_field::increment(const std::string &value, const date_time &time) const {
	date_time nextTime(time);
	nextTime -= minutes(nextTime.minute()); // reset minutes to 0
	nextTime -= hours(nextTime.hour()); // reset hour to 0
	nextTime += days(1);
	return nextTime;
}

day_of_week_field::nth_day_of_week day_of_week_field::parse_nth_day_of_week(const std::string &value) const {
	size_t pos = value.find_first_of("#");
	if (pos != std::string::npos) {
		return { value.substr(0, pos), value.substr(pos + 1) };
	}
	return nth_day_of_week();
}

std::string day_of_week_field::parse_last_day_of_week(const std::string &value) const {
	size_t pos = value.find_first_of("L");
	return pos != std::string::npos ? value.substr(0, pos) : std::string();
}

} // namespace geheb
