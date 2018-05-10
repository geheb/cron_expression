#include <set>
#include <algorithm>
#include <sstream>
#include "cron_field.h"

namespace geheb {

bool cron_field::validate(const std::string &value) const {
    if (value.empty()) return false;
    if (value == "*") return true;
    if (has_step(value)) { // e.g. */5 or 5/5 or 5-59/5
        auto values = split_step(value);
        if (values.size() != 2) return false;
        std::string range = values[0];
        if (!validate(range)) return false;
        if (values[1] == "*" || has_list(values[1]) || has_range(values[1])) return false;
        int step = std::stoi(values[1]);
        if (step < 1) return false;
        if (range == "*") {
            range = std::to_string(range_start()) + _rangeChar + std::to_string(range_end());
        }
        auto ranges = split_range(range);
        int start = from_literal(ranges[0]); 
        int end = ranges.size() > 1 ? from_literal(ranges[1]) : range_end();
        int length = end - start;
        if (end < start)
        {
            length = (range_end() - start) + range_start() + end + 2;
        }
		return step <= length;
    }
    if (has_list(value)) { // e.g. 0,5 or 1,10-20
        // check if begins or ends with comma
        if (value[0] == _listChar || value[value.size() - 1] == _listChar) return false;
        auto values = split_list(value);
        for (const std::string &v : values) {
            if (v == "*" || !validate(v)) return false;
        }
        auto list = create_list(value);
        return std::set<int>(list.begin(), list.end()).size() == list.size();
    }
    if (has_range(value)) { // e.g. 0-5
        auto ranges = split_range(value);
        if (ranges.size() != 2) return false;

        if (std::find_if(ranges.begin(), ranges.end(),
            [](const auto& s) { return s == "*" || s == "?"; }) != ranges.end()) return false;

        if (!validate(ranges[0]) || !validate(ranges[1])) return false;
        return _allowBackwardRange ? 
            from_literal(ranges[0]) != from_literal(ranges[1]) :
            from_literal(ranges[0]) < from_literal(ranges[1]);
    }
    int num = from_literal(value);
    if (num < 0) return false;
    return num >= range_start() && num <= range_end();
}

std::vector<int> cron_field::create_list(const std::string &value) const {
    std::vector<int> result;

    for (const std::string &v : split_list(value)) {
        bool hasStep = has_step(v);
        if (hasStep || has_range(v)) {
            int offset, to, step;
            if (hasStep) {
                auto values = split_step(v); // *\5 or offset[-to]/step size
                std::string range = values[0];
                step = std::stoi(values[1]);
                if (range == "*") {
                    offset = range_start();
                    to = range_end();
                }
                else {
                    values = split_range(range);
                    offset = from_literal(values[0]);
                    to = values.size() > 1 ? from_literal(values[1]) : range_end();
                }
            }
            else {
                auto values = split_range(v);
                offset = from_literal(values[0]);
                to = from_literal(values[1]);
                step = 1;
            }
            if (_allowBackwardRange && offset > to)
            {
                // e.g. FRI - TUE 4 => 5,6,0,1,2
                for (int i = offset; i <= range_end(); i += step) {
                    result.push_back(i);
                }
                for (int i = range_start(); i <= to; i += step) {
                    result.push_back(i);
                }
            }
            else
            {
                for (int i = offset; i <= to; i += step) {
                    result.push_back(i);
                }
            }
        }
        else {
            result.push_back(from_literal(v));
        }
    }

    return result;
}

int cron_field::from_literal(const std::string &value) const {
    if (!_literals.empty())    {
        auto it = _literals.find(value);
        if (it != _literals.end()) {
            return it->second;
        }
    }
    return is_numeric(value) ? std::stoi(value) : -1;
}

std::vector<std::string> cron_field::split(const std::string &value, char delimiter) const {
    std::stringstream valueStream(value);
    std::string item;
    std::vector<std::string> result;
    while (std::getline(valueStream, item, delimiter)) {
        result.push_back(std::move(item));
    }
    return result;
}

bool cron_field::is_numeric(const std::string& value) const {
    if (value.empty()) return false;
    char *p = nullptr;
    strtol(value.c_str(), &p, 10);
    return *p == 0;
}

bool cron_field::match(const std::string& value, int time) const {
    if (value == "*") return true;
    if (has_list(value) || has_range(value) || has_step(value)) {
        auto values = create_list(value);
        return std::find(values.begin(), values.end(), time) != values.end();
    }
    return time == from_literal(value);
}

} // namespace geheb
