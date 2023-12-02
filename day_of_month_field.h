#pragma once
#include "date_time.h"
#include "cron_field.h"

namespace geheb {

class day_of_month_field final : public cron_field {
public:
    int range_start() const override { return 1; }
    int range_end() const override { return 31; }
    cron_field_pos pos() const override { return cron_field_pos::day_of_month; }
    bool validate(const std::string &value) const override;
    bool match(const std::string &value, const date_time &time) const override;
    date_time increment(const std::string &value, const date_time &time) const override;

private:
    std::string parse_nearest_weekday(const std::string &value) const;
    int calc_nearest_weekday(const date_time &time) const;

};

} // namespace geheb
