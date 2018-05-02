#pragma once
#include "date_time.h"
#include "cron_field.h"

namespace geheb {

class month_field final : public cron_field {
public:
	month_field();
	int range_start() const override { return 1; }
	int range_end() const override { return 12; }
	cron_field_pos pos() const override { return cron_field_pos::month; }
	bool match(const std::string &value, const date_time &time) const override {
		return cron_field::match(value, time.month());
	}
	date_time increment(const std::string &value, const date_time &time) const override;
};

} // namespace geheb
