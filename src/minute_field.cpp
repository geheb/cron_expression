#include <algorithm>
#include "minute_field.h"

namespace geheb {

date_time minute_field::increment(const std::string &value, const date_time &time) const {
	date_time nextTime(time);
	if (value == "*") {
		nextTime += minutes(1);
		return nextTime;
	}
	int pos = -1;
	auto list = create_list(value);
	for (size_t i = 0; i < list.size() - 1 && pos < 0; i++) {
		int currentVal = list[i];
		int nextVal = list[i + 1];
		if (time.minute() >= currentVal && time.minute() < nextVal) {
			pos = i + 1;
		}
	}
	nextTime -= minutes(nextTime.minute()); // reset minutes to 0
	pos = std::max(pos, 0);
	if (time.minute() >= list[pos]) {
		nextTime += hours(1);
	}
	else {
		nextTime += minutes(list[pos]);
	}
	return nextTime;
}

} // namespace geheb
