#include <algorithm>
#include "day_of_month_field.h"

namespace geheb {

bool day_of_month_field::validate(const std::string &value) const {
	if (value == "L" || value == "?") return true;
	std::string weekday = parse_nearest_weekday(value);
	// validate that a list don't have W or L
	if (has_list(value) &&
		(!weekday.empty() || value.find_first_of("L") != std::string::npos)) {
		return false;
	}
	return cron_field::validate(!weekday.empty() ? weekday : value);
}

bool day_of_month_field::match(const std::string &value, const date_time &time) const {
	if (value == "?") return true;
	if (value == "L") { // is the last day of the month?
		return time.day() == time.last_day_of_month();
	}
	// if this is the nearest weekday to a particular value
	std::string weekday = parse_nearest_weekday(value);
	if (!weekday.empty()) {
		int targetDay = std::stoi(weekday);
		int lastDayOfMonth = time.last_day_of_month();
		if (targetDay > lastDayOfMonth) targetDay = lastDayOfMonth; // use max allowed for current month
		return time.day() == calc_nearest_weekday(date_time(time.year(), time.month(), targetDay));
	}
	return cron_field::match(value, time.day());
}

date_time day_of_month_field::increment(const std::string &value, const date_time &time) const {
	if (value == "*" || value == "L" || !parse_nearest_weekday(value).empty()) {
		date_time nextTime(time);
		nextTime -= minutes(nextTime.minute()); // reset minutes to 0
		nextTime -= hours(nextTime.hour()); // reset hours to 0
		nextTime += days(1);
		return nextTime;
	}
	int pos = -1;
	auto list = create_list(value);
	for (size_t i = 0; i < list.size() - 1 && pos < 0; i++) {
		int currentVal = list[i];
		int nextVal = list[i + 1];
		if (time.day() >= currentVal && time.day() < nextVal) {
			pos = i + 1;
		}
	}
	pos = std::max(pos, 0);
	if (time.day() >= list[pos]) {
		date_time nextTime(time.year(), time.month(), 1);
		nextTime += days(nextTime.last_day_of_month()); // next month
		return nextTime;
	}
	else {
		return date_time(time.year(), time.month(), list[pos]);
	}
}

std::string day_of_month_field::parse_nearest_weekday(const std::string &value) const {
	size_t pos = value.find_first_of("W");
	return pos != std::string::npos ? value.substr(0, pos) : std::string();
}

// is used to specify the weekday (Monday-Friday) nearest the given day
int day_of_month_field::calc_nearest_weekday(const date_time &time) const {
	if (!time.is_weekend()) return time.day();
	for (const int &offset : { -1,1,-2,2 }) {
		int dayOffset = time.day() + offset;
		if (dayOffset > 0 && dayOffset <= time.last_day_of_month()) {
			if (!date_time(time.year(), time.month(), dayOffset).is_weekend()) return dayOffset;
		}
	}
	return time.day(); // should never happen ;)
}

} // namespace geheb
