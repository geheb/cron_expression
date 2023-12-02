#include <algorithm>
#include "hour_field.h"

namespace geheb {

hour_field::hour_field() {
    _allowBackwardRange = true;
}

date_time hour_field::increment(const std::string &value, const date_time &time) const {
    date_time nextTime(time);
    nextTime -= minutes(nextTime.minute()); // reset minutes to 0
    if (value == "*") {
        nextTime += hours(1);
        return nextTime;
    }
    size_t pos = 0;
    auto list = create_list(value);
    for (size_t i = 0; i < list.size() - 1; i++) {
        int currentVal = list[i];
        int nextVal = list[i + 1];
        if (time.hour() >= currentVal && time.hour() < nextVal) {
            pos = i + 1;
            break;
        }
    }
    nextTime -= hours(nextTime.hour()); // reset hour to 0
    if (time.hour() >= list[pos]) {
        nextTime += days(1);
    }
    else {
        nextTime += hours(list[pos]);
    }
    return nextTime;
}

} // namespace geheb
