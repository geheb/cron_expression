#include <algorithm>
#include "month_field.h"

namespace geheb {

month_field::month_field() {
	_literals = {
		{ "JAN", 1 },
		{ "FEB", 2 },
		{ "MAR", 3 },
		{ "APR", 4 },
		{ "MAY", 5 },
		{ "JUN", 6 },
		{ "JUL", 7 },
		{ "AUG", 8 },
		{ "SEP", 9 },
		{ "OCT", 10 },
		{ "NOV", 11 },
		{ "DEC", 12 }
	};
}

date_time month_field::increment(const std::string &value, const date_time &time) const {
	if (value == "*") {
		date_time nextTime(time.year(), time.month(), 1);
		nextTime += days(nextTime.last_day_of_month());
		return nextTime;
	}
	int pos = -1;
	auto list = create_list(value);
	for (size_t i = 0; i < list.size() - 1 && pos < 0; i++)	{
		int currentVal = list[i];
		int nextVal = list[i + 1];
		if (time.month() >= currentVal && time.month() < nextVal) {
			pos = i + 1;
		}
	}
	pos = std::max(pos, 0);
	if (time.month() >= list[pos]) {
		return date_time(time.year() + 1, 1, 1);
	}
	else {
		return date_time(time.year(), list[pos], 1);
	}
}

} // namespace geheb
