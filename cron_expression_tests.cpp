#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "cron_expression.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("cron_expression: every minute is valid", "[cron_expression]") {
    REQUIRE_NOTHROW(cron_expression("* * * * *"));
}

TEST_CASE("cron_expression: every minute matches time", "[cron_expression]") {
    const cron_expression cron("* * * * *");
    REQUIRE(date_time(2018, 1, 1, 1, 2) == cron.calc_next(date_time(2018, 1, 1, 1, 1)));
    REQUIRE(date_time(2018, 1, 1, 2, 0) == cron.calc_next(date_time(2018, 1, 1, 1, 59)));
    REQUIRE(date_time(2018, 1, 2, 0, 0) == cron.calc_next(date_time(2018, 1, 1, 23, 59)));
    REQUIRE(date_time(2018, 2, 1, 0, 0) == cron.calc_next(date_time(2018, 1, 31, 23, 59)));
    REQUIRE(date_time(2019, 1, 1, 0, 0) == cron.calc_next(date_time(2018, 12, 31, 23, 59)));
    REQUIRE(date_time(2000, 2, 29, 0, 0) == cron.calc_next(date_time(2000, 2, 28, 23, 59))); // check also leap year
}