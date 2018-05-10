#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "minute_field.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("minute_field: configuration is valid", "[minute_field]") {
    const minute_field minute;
    REQUIRE(minute.range_start() == 0);
    REQUIRE(minute.range_end() == 59);
    REQUIRE(minute.pos() == cron_field_pos::minute);
}

TEST_CASE("minute_field: value 0-59 is valid", "[minute_field]") {
    const minute_field minute;
    for (int i = 0; i < 60; i++) {
        REQUIRE(minute.validate(std::to_string(i)));
    }
}

TEST_CASE("minute_field: value 0-59 matches date_time", "[minute_field]") {
    const minute_field minute;
    for (int i = 0; i < 60; i++) {
        REQUIRE(minute.match(to_string(i), date_time(2018, 1, 1, 0, i)));
    }
}

TEST_CASE("minute_field: pattern every minute is valid", "[minute_field]") {
    const minute_field minute;
    REQUIRE(minute.validate("*"));
    REQUIRE(minute.validate("*/1"));
    REQUIRE(minute.validate("0/1"));
    REQUIRE(minute.validate("0-59/1"));
    REQUIRE(minute.validate("0-59"));
    REQUIRE(minute.validate(
        "0,1,2,3,4,5,6,7,8,9,"
        "10,11,12,13,14,15,16,17,18,19,"
        "20,21,22,23,24,25,26,27,28,29,"
        "30,31,32,33,34,35,36,37,38,39,"
        "40,41,42,43,44,45,46,47,48,49,"
        "50,51,52,53,54,55,56,57,58,59"));
}

TEST_CASE("minute_field: pattern every minute matches current time", "[minute_field]") {
    const minute_field minute;
    REQUIRE(minute.match("*", date_time::now()));
    REQUIRE(minute.match("*/1", date_time::now()));
    REQUIRE(minute.match("0/1", date_time::now()));
    REQUIRE(minute.match("0-59/1", date_time::now()));
    REQUIRE(minute.match("0-59", date_time::now()));
    REQUIRE(minute.match(
        "0,1,2,3,4,5,6,7,8,9,"
        "10,11,12,13,14,15,16,17,18,19,"
        "20,21,22,23,24,25,26,27,28,29,"
        "30,31,32,33,34,35,36,37,38,39,"
        "40,41,42,43,44,45,46,47,48,49,"
        "50,51,52,53,54,55,56,57,58,59", date_time::now()));
}

TEST_CASE("minute_field: pattern every 5 minutes is valid", "[minute_field]") {
    const minute_field minute;
    REQUIRE(minute.validate("*/5"));
    REQUIRE(minute.validate("0/5"));
    REQUIRE(minute.validate("0-59/5"));
    REQUIRE(minute.validate("56-0/5"));
    REQUIRE(minute.validate("0,5,10,15,20,25,30,35,40,45,50,55"));
}

TEST_CASE("minute_field: pattern every 5 minutes matches date_time", "[minute_field]") {
    const minute_field minute;
    for (int i = 0; i < 60; i+=5) {
        const auto time = date_time(2018, 1, 1, 0, i);
        REQUIRE(minute.match("*/5", time));
        REQUIRE(minute.match("0/5", time));
        REQUIRE(minute.match("0-59/5", time));
        REQUIRE(minute.match("0,5,10,15,20,25,30,35,40,45,50,55", time));
    }
}

TEST_CASE("minute_field: list and range values are valid", "[minute_field]") {
    const minute_field minute;
    REQUIRE(minute.validate("0"));
    REQUIRE(minute.validate("0-15,39,45"));
    REQUIRE(minute.validate("0-15,30-45"));
    REQUIRE(minute.validate("3,2,1"));
    REQUIRE(minute.validate("55-5"));
}

TEST_CASE("minute_field: out of range values are invalid", "[minute_field]") {
    const minute_field minute;
    REQUIRE(!minute.validate("60"));
    REQUIRE(!minute.validate("590"));
}

TEST_CASE("minute_field: range values are invalid", "[minute_field]") {
    const minute_field minute;
    REQUIRE(!minute.validate("-"));
    REQUIRE(!minute.validate("*-"));
    REQUIRE(!minute.validate("-*"));
    REQUIRE(!minute.validate("*-*"));
    REQUIRE(!minute.validate("0-0"));
    REQUIRE(!minute.validate("0-60"));
    REQUIRE(!minute.validate("60-0"));
    REQUIRE(!minute.validate("1-"));
    REQUIRE(!minute.validate("1-*"));
    REQUIRE(!minute.validate("1-?"));
    REQUIRE(!minute.validate("-59"));
}

TEST_CASE("minute_field: step values are invalid", "[minute_field]") {
    const minute_field minute;
    REQUIRE(!minute.validate("/"));
    REQUIRE(!minute.validate("*/*"));
    REQUIRE(!minute.validate("/*"));
    REQUIRE(!minute.validate("*/"));
    REQUIRE(!minute.validate("*/0"));
    REQUIRE(!minute.validate("/0"));
    REQUIRE(!minute.validate("0/0"));
    REQUIRE(!minute.validate("/0-59"));
    REQUIRE(!minute.validate("0/0-59"));
    REQUIRE(!minute.validate("0-59/0"));
    REQUIRE(!minute.validate("0/60"));
    REQUIRE(!minute.validate("*/60"));
    REQUIRE(!minute.validate("1-1/1"));
    REQUIRE(!minute.validate("*/1/1"));
}

TEST_CASE("minute_field: list values are invalid", "[minute_field]") {
    const minute_field minute;
    REQUIRE(!minute.validate(","));
    REQUIRE(!minute.validate("*,"));
    REQUIRE(!minute.validate(",*"));
    REQUIRE(!minute.validate("*,*"));
    REQUIRE(!minute.validate("*,0"));
    REQUIRE(!minute.validate("0,*"));
    REQUIRE(!minute.validate("*/5,*/5"));
    REQUIRE(!minute.validate("*/5,*"));
    REQUIRE(!minute.validate("0,6,100"));
    REQUIRE(!minute.validate("0,1,2,3,0"));
    REQUIRE(!minute.validate(",0"));
    REQUIRE(!minute.validate("0,"));
}

TEST_CASE("minute_field: non numeric values are invalid", "[minute_field]") {
    const minute_field minute;
    REQUIRE(!minute.validate("60"));
    REQUIRE(!minute.validate("?"));
    REQUIRE(!minute.validate("W"));
    REQUIRE(!minute.validate("1W"));
    REQUIRE(!minute.validate("L"));
    REQUIRE(!minute.validate("1L"));
    REQUIRE(!minute.validate("1#1"));
    REQUIRE(!minute.validate("JAN"));
    REQUIRE(!minute.validate("MON"));
}
