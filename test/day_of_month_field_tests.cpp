#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "day_of_month_field.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("day_of_month_field: configuration is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(mday.range_start() == 1);
    REQUIRE(mday.range_end() == 31);
    REQUIRE(mday.pos() == cron_field_pos::day_of_month);
}

TEST_CASE("day_of_month_field: value 1-31 is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    for (int i = 1; i <= 31; i++) {
        REQUIRE(mday.validate(std::to_string(i)));
    }
}

TEST_CASE("day_of_month_field: value 1-31 matches date_time", "[day_of_month_field]") {
    const day_of_month_field mday;
    const int daycount[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    for (int m = 0; m < 12; m++) {
        for (int d = 1; d <= daycount[m]; d++) {
            REQUIRE(mday.match(to_string(d), date_time(2018, m + 1, d)));
        }
    }
    
    for (int i = 1; i <= 29; i++) {
        REQUIRE(mday.match(to_string(i), date_time(2000, 2, i)));
    }
}

TEST_CASE("day_of_month_field: nearest week day is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    for (int i = 1; i <= 31; i++) {
        REQUIRE(mday.validate(std::to_string(i) + "W"));
    }
}

TEST_CASE("day_of_month_field: pattern every day is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(mday.validate("*"));
    REQUIRE(mday.validate("*/1"));
    REQUIRE(mday.validate("1/1"));
    REQUIRE(mday.validate("1-31/1"));
    REQUIRE(mday.validate("1-31"));
    REQUIRE(mday.validate(
        "1,2,3,4,5,6,7,"
        "8,9,10,11,12,13,"
        "14,15,16,17,18,19,"
        "20,21,22,23,24,25,"
        "26,27,28,29,30,31"));
}

TEST_CASE("day_of_month_field: pattern every day matches current time", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(mday.match("*", date_time::now()));
    REQUIRE(mday.match("*/1", date_time::now()));
    REQUIRE(mday.match("1/1", date_time::now()));
    REQUIRE(mday.match("1-31/1", date_time::now()));
    REQUIRE(mday.match("1-31", date_time::now()));
    REQUIRE(mday.match(
        "1,2,3,4,5,6,7,"
        "8,9,10,11,12,13,"
        "14,15,16,17,18,19,"
        "20,21,22,23,24,25,"
        "26,27,28,29,30,31", date_time::now()));
}

TEST_CASE("day_of_month_field: pattern every 5 days is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(mday.validate("*/5"));
    REQUIRE(mday.validate("1/5"));
    REQUIRE(mday.validate("1-31/5"));
    REQUIRE(mday.validate("1,6,11,16,21,26,31"));
}

TEST_CASE("day_of_month_field: pattern every 5 days matches date_time", "[day_of_month_field]") {
    const day_of_month_field mday;
    for (int i = 1; i <= 31; i += 5) {
        const auto time = date_time(2018, 1, i);
        REQUIRE(mday.match("*/5", time));
        REQUIRE(mday.match("1/5", time));
        REQUIRE(mday.match("1-31/5", time));
        REQUIRE(mday.match("1,6,11,16,21,26,31", time));
    }
}

TEST_CASE("day_of_month_field: list and range values are valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(mday.validate("1"));
    REQUIRE(mday.validate("1-6,7,8"));
    REQUIRE(mday.validate("1-3,6-9"));
    REQUIRE(mday.validate("3,2,1"));
}

TEST_CASE("day_of_month_field: special char is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(mday.validate("L"));
    REQUIRE(mday.validate("?"));
}

TEST_CASE("day_of_month_field: out of range values are invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(!mday.validate("0"));
    REQUIRE(!mday.validate("32"));
    REQUIRE(!mday.validate("310"));
}

TEST_CASE("day_of_month_field: range values are invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(!mday.validate("-"));
    REQUIRE(!mday.validate("*-"));
    REQUIRE(!mday.validate("-*"));
    REQUIRE(!mday.validate("*-*"));
    REQUIRE(!mday.validate("1-1"));
    REQUIRE(!mday.validate("1-32"));
    REQUIRE(!mday.validate("32-1"));
    REQUIRE(!mday.validate("1-"));
    REQUIRE(!mday.validate("1-*"));
    REQUIRE(!mday.validate("1-?"));
    REQUIRE(!mday.validate("-31"));
}

TEST_CASE("day_of_month_field: step values are invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(!mday.validate("/"));
    REQUIRE(!mday.validate("*/*"));
    REQUIRE(!mday.validate("/*"));
    REQUIRE(!mday.validate("*/"));
    REQUIRE(!mday.validate("*/0"));
    REQUIRE(!mday.validate("/0"));
    REQUIRE(!mday.validate("0/0"));
    REQUIRE(!mday.validate("/1-31"));
    REQUIRE(!mday.validate("0/1-31"));
    REQUIRE(!mday.validate("1-31/0"));
    REQUIRE(!mday.validate("0/31"));
    REQUIRE(!mday.validate("*/31"));
    REQUIRE(!mday.validate("1-1/1"));
    REQUIRE(!mday.validate("*/1/1"));
}

TEST_CASE("day_of_month_field: list values are invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(!mday.validate(","));
    REQUIRE(!mday.validate("*,"));
    REQUIRE(!mday.validate(",*"));
    REQUIRE(!mday.validate("*,*"));
    REQUIRE(!mday.validate("*,1"));
    REQUIRE(!mday.validate("1,*"));
    REQUIRE(!mday.validate("*/5,*/5"));
    REQUIRE(!mday.validate("*/5,*"));
    REQUIRE(!mday.validate("1,6,100"));
    REQUIRE(!mday.validate("1,2,3,1"));
    REQUIRE(!mday.validate(",1"));
    REQUIRE(!mday.validate("1,"));
}

TEST_CASE("day_of_month_field: non numeric values are invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(!mday.validate("32"));
    REQUIRE(!mday.validate("W"));
    REQUIRE(!mday.validate("1L"));
    REQUIRE(!mday.validate("1#1"));
    REQUIRE(!mday.validate("JAN"));
    REQUIRE(!mday.validate("MON"));
}
