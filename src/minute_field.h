#pragma once
#include "date_time.h"
#include "cron_field.h"

namespace geheb {

class minute_field final : public cron_field {
public:
	int range_start() const override { return 0; }
	int range_end() const override { return 59; }
	cron_field_pos pos() const override { return cron_field_pos::minute; }
	bool match(const std::string &value, const date_time &time) const override {
		return cron_field::match(value, time.minute());
	}
	date_time increment(const std::string &value, const date_time &time) const override;
};

} // namespace geheb

