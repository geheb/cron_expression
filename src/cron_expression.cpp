#include <sstream>
#include <iterator>
#include "cron_expression.h"
#include "cron_field.h"
#include "minute_field.h"
#include "hour_field.h"
#include "day_of_month_field.h"
#include "month_field.h"
#include "day_of_week_field.h"

namespace geheb {

cron_expression::cron_expression(const std::string &expression) {
	std::istringstream buffer(expression);
	std::vector<std::string> tokens	{
		std::istream_iterator<std::string>(buffer),
		std::istream_iterator<std::string>()
	};
	if (tokens.size() != 5)	{
		throw std::invalid_argument("invalid cron expression, only 5 definitions allowed");
	}
	_values[cron_field_pos::minute] = tokens[0];
	_values[cron_field_pos::hour] = tokens[1];
	_values[cron_field_pos::day_of_month] = tokens[2];
	_values[cron_field_pos::month] = tokens[3];
	_values[cron_field_pos::day_of_week] = tokens[4];

	if (!minute_field().validate(_values[cron_field_pos::minute])) throw std::invalid_argument("invalid minute field");
	if (!hour_field().validate(_values[cron_field_pos::hour])) throw std::invalid_argument("invalid hour field");
	if (!day_of_month_field().validate(_values[cron_field_pos::day_of_month])) throw std::invalid_argument("invalid day of month field");
	if (!month_field().validate(_values[cron_field_pos::month])) throw std::invalid_argument("invalid month field");
	if (!day_of_week_field().validate(_values[cron_field_pos::day_of_week])) throw std::invalid_argument("invalid day of week field");
}

system_clock::time_point cron_expression::calc_next(const system_clock::time_point &timePoint) {
	date_time nextTime(timePoint);
	month_field month;
	day_of_month_field day;
	day_of_week_field dow;
	hour_field hour;
	minute_field minute;
	// this order is required to test cron parts
	const cron_field *fields[5] = { &month, &day, &dow, &hour, &minute };
	// run max 1000 iterations
	for (int i = 0; i < 1000; i++) {
		bool startOver = false;

		for (const cron_field *f : fields) {

			const std::string &value = _values[f->pos()];
			if (value == "*") continue;
			bool matched = false;

			if (f->has_list(value)) {
				for (const std::string &v : f->split_list(value)) {
					if (f->match(v, nextTime)) {
						matched = true;
						break;
					}
				}
			}
			else {
				if (f->match(value, nextTime)) matched = true;
			}
			if (!matched) {
				// increment time and start over
				nextTime = f->increment(value, nextTime);
				startOver = true;
				break;
			}
		}
		if (startOver) continue;

		if ((system_clock::time_point)nextTime == timePoint) {
			// increment minute
			const std::string& value = _values[cron_field_pos::minute];
			nextTime = minute.increment(value, nextTime);
			continue;
		}
		return nextTime;
	}
	return system_clock::time_point();
}

} // namespace geheb
