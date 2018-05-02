#pragma once
#include "date_time.h"
#include "cron_field.h"

namespace geheb {

class day_of_week_field final : public cron_field {
public:
	day_of_week_field();
	int range_start() const override { return 0; }
	int range_end() const override { return 6; }
	cron_field_pos pos() const override { return cron_field_pos::day_of_week; }
	bool validate(const std::string &value) const override;
	bool match(const std::string &value, const date_time &time) const override;
	date_time increment(const std::string &value, const date_time &time) const override;

private:
	struct nth_day_of_week {
		std::string day;
		std::string count;
		bool has_values() const { return !day.empty(); }
	};
	nth_day_of_week parse_nth_day_of_week(const std::string &value) const;
	std::string parse_last_day_of_week(const std::string &value) const;

};

} // namespace geheb
