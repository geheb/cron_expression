#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "day_of_week_field.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("day_of_week_field: configuration is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(wday.range_start() == 0);
    REQUIRE(wday.range_end() == 6);
    REQUIRE(wday.pos() == cron_field_pos::day_of_week);
}

TEST_CASE("day_of_week_field: value 0-6 is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    for (int i = 0; i <= 6; i++) {
        REQUIRE(wday.validate(std::to_string(i)));
    }
}

TEST_CASE("day_of_week_field: value SUN-SAT is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    const char* wdays[7] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
    for (const char* d : wdays) {
        REQUIRE(wday.validate(d));
    }
}

TEST_CASE("day_of_week_field: nth day of the week of every day is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    for (int i = 0; i < 7; i++) {
        for (int j = 1; j < 6; j++) {
            REQUIRE(wday.validate(to_string(i) + "#" + to_string(j)));
        }
    }
}

TEST_CASE("day_of_week_field: last day of week is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    for (int i = 0; i < 7; i++) {
        REQUIRE(wday.validate(to_string(i) + "L"));
    }
}


TEST_CASE("day_of_week_field: value 0-6 matches date_time", "[day_of_week_field]") {
    const day_of_week_field wday;
    for (int i = 0; i <= 6; i++) {
        REQUIRE(wday.match(to_string(i), date_time(2018, 4, 1 + i)));
    }
}

TEST_CASE("day_of_week_field: pattern every day of week is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(wday.validate("*"));
    REQUIRE(wday.validate("*/1"));
    REQUIRE(wday.validate("0/1"));
    REQUIRE(wday.validate("0-6/1"));
    REQUIRE(wday.validate("1-0/1"));
    REQUIRE(wday.validate("0-6"));
    REQUIRE(wday.validate("1-0"));
    REQUIRE(wday.validate("0,1,2,3,4,5,6"));
    REQUIRE(wday.validate("1,2,3,4,5,6,0"));
    REQUIRE(wday.validate("SUN,MON,TUE,WED,THU,FRI,SAT"));
    REQUIRE(wday.validate("MON,TUE,WED,THU,FRI,SAT,SUN"));
    REQUIRE(wday.validate("SUN-SAT"));
    REQUIRE(wday.validate("MON-SUN"));
}

TEST_CASE("day_of_week_field: pattern every day of week matches current time", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(wday.match("*", date_time::now()));
    REQUIRE(wday.match("*/1", date_time::now()));
    REQUIRE(wday.match("0/1", date_time::now()));
    REQUIRE(wday.match("0-6/1", date_time::now()));
    REQUIRE(wday.match("1-0/1", date_time::now()));
    REQUIRE(wday.match("0-6", date_time::now()));
    REQUIRE(wday.match("1-0", date_time::now()));
    REQUIRE(wday.match("0,1,2,3,4,5,6", date_time::now()));
    REQUIRE(wday.match("1,2,3,4,5,6,0", date_time::now()));
    REQUIRE(wday.match("SUN,MON,TUE,WED,THU,FRI,SAT", date_time::now()));
    REQUIRE(wday.match("MON,TUE,WED,THU,FRI,SAT,SUN", date_time::now()));
    REQUIRE(wday.match("SUN-SAT", date_time::now()));
    REQUIRE(wday.match("MON-SUN", date_time::now()));
}

TEST_CASE("day_of_week_field: pattern every 2 days of week is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(wday.validate("*/2"));
    REQUIRE(wday.validate("1/2"));
    REQUIRE(wday.validate("TUE/2"));
    REQUIRE(wday.validate("0-6/2"));
    REQUIRE(wday.validate("SUN-SAT/2"));
    REQUIRE(wday.validate("MON-SUN/2"));
    REQUIRE(wday.validate("0,2,4,6"));
    REQUIRE(wday.validate("0,2,THU,SAT"));
    REQUIRE(wday.validate("0-2/2"));
    REQUIRE(wday.validate("6-5/2"));
}

TEST_CASE("day_of_week_field: pattern every 2 days of week matches date_time", "[day_of_week_field]") {
    const day_of_week_field wday;
    for (int i = 0; i <= 6; i += 2) {
        const auto time = date_time(2018, 4, 1 + i);
        REQUIRE(wday.match("*/2", time));
        REQUIRE(wday.match("0/2", time));
        REQUIRE(wday.match("SUN/2", time));
        REQUIRE(wday.match("0-6/2", time));
        REQUIRE(wday.match("SUN-SAT/2", time));
        REQUIRE(wday.match("0,2,4,6", time));
        REQUIRE(wday.match("0,2,THU,SAT", time));
    }
}

TEST_CASE("day_of_week_field: list and range values are valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(wday.validate("1"));
    REQUIRE(wday.validate("1-3,5,6"));
    REQUIRE(wday.validate("0-3,4-6"));
    REQUIRE(wday.validate("3,2,1"));
    REQUIRE(wday.validate("0-6"));
    REQUIRE(wday.validate("6-0"));
    REQUIRE(wday.validate("1-0/6"));
}

TEST_CASE("day_of_week_field: special char is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(wday.validate("?"));
}

TEST_CASE("day_of_week_field: out of range values are invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(!wday.validate("7"));
    REQUIRE(!wday.validate("60"));
}

TEST_CASE("day_of_week_field: range values are invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(!wday.validate("1-3/3"));
    REQUIRE(!wday.validate("-"));
    REQUIRE(!wday.validate("*-"));
    REQUIRE(!wday.validate("*-1"));
    REQUIRE(!wday.validate("-*"));
    REQUIRE(!wday.validate("1-*"));
    REQUIRE(!wday.validate("*-*"));
    REQUIRE(!wday.validate("0-0"));
    REQUIRE(!wday.validate("0-7"));
    REQUIRE(!wday.validate("7-0"));
    REQUIRE(!wday.validate("0-"));
    REQUIRE(!wday.validate("1-7"));
    REQUIRE(!wday.validate("0-?"));
    REQUIRE(!wday.validate("?-6"));
    REQUIRE(!wday.validate("?-?"));
    REQUIRE(!wday.validate("-6"));
}

TEST_CASE("day_of_week_field: step values are invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(!wday.validate("/"));
    REQUIRE(!wday.validate("*/*"));
    REQUIRE(!wday.validate("/*"));
    REQUIRE(!wday.validate("*/"));
    REQUIRE(!wday.validate("*/0"));
    REQUIRE(!wday.validate("/0"));
    REQUIRE(!wday.validate("0/0"));
    REQUIRE(!wday.validate("/0-6"));
    REQUIRE(!wday.validate("0/0-6"));
    REQUIRE(!wday.validate("0-6/0"));
    REQUIRE(!wday.validate("0/7"));
    REQUIRE(!wday.validate("0-6/7"));
    REQUIRE(!wday.validate("*/7"));
    REQUIRE(!wday.validate("1-1/1"));
    REQUIRE(!wday.validate("*/1/1"));
    REQUIRE(!wday.validate("1-0/7"));
}

TEST_CASE("day_of_week_field: list values are invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(!wday.validate(","));
    REQUIRE(!wday.validate("*,"));
    REQUIRE(!wday.validate(",*"));
    REQUIRE(!wday.validate("*,*"));
    REQUIRE(!wday.validate("*,1"));
    REQUIRE(!wday.validate("1,*"));
    REQUIRE(!wday.validate("*/2,*/2"));
    REQUIRE(!wday.validate("*/2,*"));
    REQUIRE(!wday.validate("1,6,100"));
    REQUIRE(!wday.validate("1,2,3,1"));
    REQUIRE(!wday.validate(",1"));
    REQUIRE(!wday.validate("1,"));
}

TEST_CASE("day_of_week_field: non numeric values are invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(!wday.validate("7"));
    REQUIRE(!wday.validate("W"));
    REQUIRE(!wday.validate("1W"));
    REQUIRE(!wday.validate("L"));
    REQUIRE(!wday.validate("JAN"));
    REQUIRE(!wday.validate("0#6"));
    REQUIRE(!wday.validate("1#7"));
}
