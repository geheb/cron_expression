#pragma once
#include <string>
#include <chrono>

namespace geheb {

using namespace std::chrono;

class cron_expression final {
public:
    cron_expression(const std::string &expression);
    system_clock::time_point calc_next(const system_clock::time_point &timePoint) const;

private:
    std::string _values[5];

};

} // namespace geheb
