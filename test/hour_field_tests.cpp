#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "hour_field.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("hour_field: configuration is valid", "[hour_field]") {
    const hour_field hour;
    REQUIRE(hour.range_start() == 0);
    REQUIRE(hour.range_end() == 23);
    REQUIRE(hour.pos() == cron_field_pos::hour);
}

TEST_CASE("hour_field: value 0-23 is valid", "[hour_field]") {
    const hour_field hour;
    for (int i = 0; i < 24; i++) {
        REQUIRE(hour.validate(std::to_string(i)));
    }
}

TEST_CASE("hour_field: value 0-23 matches date_time", "[hour_field]") {
    const hour_field hour;
    for (int i = 0; i < 24; i++) {
        REQUIRE(hour.match(to_string(i), date_time(2018, 1, 1, i)));
    }
}

TEST_CASE("hour_field: pattern every hour is valid", "[hour_field]") {
    const hour_field hour;
    REQUIRE(hour.validate("*"));
    REQUIRE(hour.validate("*/1"));
    REQUIRE(hour.validate("0/1"));
    REQUIRE(hour.validate("0-23/1"));
    REQUIRE(hour.validate("0-23"));
    REQUIRE(hour.validate(
        "0,1,2,3,4,5,6,"
        "7,8,9,10,11,12,"
        "13,14,15,16,17,18,"
        "19,20,21,22,23"));
}

TEST_CASE("hour_field: pattern every hour matches current time", "[hour_field]") {
    const hour_field hour;
    REQUIRE(hour.match("*", date_time::now()));
    REQUIRE(hour.match("*/1", date_time::now()));
    REQUIRE(hour.match("0/1", date_time::now()));
    REQUIRE(hour.match("0-23/1", date_time::now()));
    REQUIRE(hour.match("0-23", date_time::now()));
    REQUIRE(hour.match(
        "0,1,2,3,4,5,6,"
        "7,8,9,10,11,12,"
        "13,14,15,16,17,18,"
        "19,20,21,22,23", date_time::now()));
}

TEST_CASE("hour_field: pattern every 5 hours is valid", "[hour_field]") {
    const hour_field hour;
    REQUIRE(hour.validate("*/5"));
    REQUIRE(hour.validate("0/5"));
    REQUIRE(hour.validate("0-23/5"));
    REQUIRE(hour.validate("0,5,10,15,20"));
}

TEST_CASE("hour_field: pattern every 5 hours matches date_time", "[hour_field]") {
    const hour_field hour;
    for (int i = 0; i < 24; i += 5) {
        const auto time = date_time(2018, 1, 1, i);
        REQUIRE(hour.match("*/5", time));
        REQUIRE(hour.match("0/5", time));
        REQUIRE(hour.match("0-23/5", time));
        REQUIRE(hour.match("0,5,10,15,20", time));
    }
}

TEST_CASE("hour_field: list and range values are valid", "[hour_field]") {
    const hour_field hour;
    REQUIRE(hour.validate("0"));
    REQUIRE(hour.validate("0-6,7,8"));
    REQUIRE(hour.validate("0-3,6-9"));
    REQUIRE(hour.validate("3,2,1"));
}

TEST_CASE("hour_field: out of range values are invalid", "[hour_field]") {
    const hour_field hour;
    REQUIRE(!hour.validate("24"));
    REQUIRE(!hour.validate("230"));
}

TEST_CASE("hour_field: range values are invalid", "[hour_field]") {
    const hour_field hour;
    REQUIRE(!hour.validate("-"));
    REQUIRE(!hour.validate("*-"));
    REQUIRE(!hour.validate("-*"));
    REQUIRE(!hour.validate("*-*"));
    REQUIRE(!hour.validate("0-0"));
    REQUIRE(!hour.validate("0-24"));
    REQUIRE(!hour.validate("24-0"));
    REQUIRE(!hour.validate("1-"));
    REQUIRE(!hour.validate("1-*"));
    REQUIRE(!hour.validate("1-?"));
    REQUIRE(!hour.validate("-23"));
}

TEST_CASE("hour_field: step values are invalid", "[hour_field]") {
    const hour_field hour;
    REQUIRE(!hour.validate("/"));
    REQUIRE(!hour.validate("*/*"));
    REQUIRE(!hour.validate("/*"));
    REQUIRE(!hour.validate("*/"));
    REQUIRE(!hour.validate("*/0"));
    REQUIRE(!hour.validate("/0"));
    REQUIRE(!hour.validate("0/0"));
    REQUIRE(!hour.validate("/0-23"));
    REQUIRE(!hour.validate("0/0-23"));
    REQUIRE(!hour.validate("0-23/0"));
    REQUIRE(!hour.validate("0/24"));
    REQUIRE(!hour.validate("*/24"));
    REQUIRE(!hour.validate("1-1/1"));
    REQUIRE(!hour.validate("*/1/1"));
}

TEST_CASE("hour_field: list values are invalid", "[hour_field]") {
    const hour_field hour;
    REQUIRE(!hour.validate(","));
    REQUIRE(!hour.validate("*,"));
    REQUIRE(!hour.validate(",*"));
    REQUIRE(!hour.validate("*,*"));
    REQUIRE(!hour.validate("*,0"));
    REQUIRE(!hour.validate("0,*"));
    REQUIRE(!hour.validate("*/5,*/5"));
    REQUIRE(!hour.validate("*/5,*"));
    REQUIRE(!hour.validate("0,6,100"));
    REQUIRE(!hour.validate("0,1,2,3,0"));
    REQUIRE(!hour.validate(",0"));
    REQUIRE(!hour.validate("0,"));
}

TEST_CASE("hour_field: non numeric values are invalid", "[hour_field]") {
    const hour_field hour;
    REQUIRE(!hour.validate("24"));
    REQUIRE(!hour.validate("?"));
    REQUIRE(!hour.validate("W"));
    REQUIRE(!hour.validate("1W"));
    REQUIRE(!hour.validate("L"));
    REQUIRE(!hour.validate("1L"));
    REQUIRE(!hour.validate("1#1"));
    REQUIRE(!hour.validate("JAN"));
    REQUIRE(!hour.validate("MON"));
}
