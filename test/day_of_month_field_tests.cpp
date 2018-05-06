#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "day_of_month_field.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("day_of_month_field range start is 1", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(mday.range_start() == 1);
}

TEST_CASE("day_of_month_field range end is 31", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(mday.range_end() == 31);
}

TEST_CASE("day_of_month_field pos is 2", "[day_of_month_field]") {
    const day_of_month_field mday;
    REQUIRE(mday.pos() == cron_field_pos::day_of_month);
}

TEST_CASE("day_of_month_field with specific day is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    for (int i = 1; i < 32; i++)
    {
        bool valid = mday.validate(std::to_string(i));
        REQUIRE(valid);
    }
}

TEST_CASE("day_of_month_field with every day is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("*");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with every day step is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("*/1");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with every day range is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1-31");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with every day list is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate(
        "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,"
        "17,18,19,20,21,22,23,24,25,26,27,28,29,30,31");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with specific nearest week day is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    for (int i = 1; i < 32; i++)
    {
        bool valid = mday.validate(std::to_string(i) + "W");
        REQUIRE(valid);
    }
}

TEST_CASE("day_of_month_field with every 7 days is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("*/7");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with every 7 days step is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1-31/7");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with every 7 days step begining at 7 is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("7/7");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with range within list is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1-6,9,12");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with multiple ranges within list is valid ", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1-6,12-18");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with unordered list is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("3,2,1,5");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with last day of month is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("L");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with current day is valid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("?");
    REQUIRE(valid);
}

TEST_CASE("day_of_month_field with last day list is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1,2,L");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with nearest weekday list is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1,2,1W");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with current day list is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1,2,?");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with current day range is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1-?");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with excessive range values is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1-60");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with excessive list values is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1,60,100");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with day 32 is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("32");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with non numeric char is invalid", "[hour_field]") {
    const day_of_month_field hour;
    bool valid = hour.validate("D");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with nearest week day without day is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("W");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with nearest week day begining at 0 is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("0W");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with nearest week day begining at 32 is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("32W");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with missing range start is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("-31");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with missing range end is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1-");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with duplicate list values is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1-5,1,2,3");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with star and value list is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("*,0");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with star range is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("*-*");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with star and value range is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("*-31");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with value and star range is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("1-*");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with descending range is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("31-1");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with empty range is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("-");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with empty list is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate(",");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with empty step is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("/");
    REQUIRE(!valid);
}

TEST_CASE("day_of_month_field with same range values is invalid", "[day_of_month_field]") {
    const day_of_month_field mday;
    bool valid = mday.validate("0-0");
    REQUIRE(!valid);
}
