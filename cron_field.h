#pragma once
#include <string>
#include <vector>
#include <map>
#include "date_time.h"

namespace geheb {

enum cron_field_pos {
    minute = 0,
    hour = 1,
    day_of_month = 2,
    month = 3,
    day_of_week = 4
};

class cron_field {
public:
    cron_field() : _allowBackwardRange(false) {}
    virtual ~cron_field() {}
    virtual int range_start() const = 0;
    virtual int range_end() const = 0;
    virtual cron_field_pos pos() const = 0;
    virtual bool validate(const std::string &value) const;
    virtual bool match(const std::string &value, const date_time &time) const = 0;
    virtual date_time increment(const std::string &value, const date_time &time) const = 0;
    bool has_step(const std::string &value) const {
        return value.find_first_of(_stepChar) != std::string::npos;
    }
    bool has_range(const std::string &value) const {
        return value.find_first_of(_rangeChar) != std::string::npos;
    }
    bool has_list(const std::string &value) const {
        return value.find_first_of(_listChar) != std::string::npos;
    }
    std::vector<std::string> split_step(const std::string &value) const {
        return split(value, _stepChar);
    }
    std::vector<std::string> split_range(const std::string &value) const {
        return split(value, _rangeChar);
    }
    std::vector<std::string> split_list(const std::string &value) const    {
        return split(value, _listChar);
    }

private:
    const char _stepChar = '/';
    const char _rangeChar = '-';
    const char _listChar = ',';

protected:
    std::map<std::string, int> _literals;
    bool _allowBackwardRange;
    std::vector<int> create_list(const std::string &value) const;
    int from_literal(const std::string &value) const;
    std::vector<std::string> split(const std::string &value, char delimiter) const;
    bool is_numeric(const std::string& value) const;
    bool match(const std::string& value, int time) const;

};

} // namespace geheb
