#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "hour_field.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("hour_field range start is 0", "[hour_field]") {
    const hour_field hour;
    REQUIRE(hour.range_start() == 0);
}

TEST_CASE("hour_field range end is 23", "[hour_field]") {
    const hour_field hour;
    REQUIRE(hour.range_end() == 23);
}

TEST_CASE("hour_field pos is 1", "[hour_field]") {
    const hour_field hour;
    REQUIRE(hour.pos() == cron_field_pos::hour);
}

TEST_CASE("hour_field with specific hour is valid", "[hour_field]") {
    const hour_field hour;
    for (int i = 0; i < 23; i++)
    {
        bool valid = hour.validate(std::to_string(i));
        REQUIRE(valid);
    }
}

TEST_CASE("hour_field with every hour is valid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("*");
    REQUIRE(valid);
}

TEST_CASE("hour_field with every hour step is valid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("*/1");
    REQUIRE(valid);
}

TEST_CASE("hour_field with every hour range is valid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("0-23");
    REQUIRE(valid);
}

TEST_CASE("hour_field with every hour list is valid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate(
        "0,1,2,3,4,5,6,"
        "7,8,9,10,11,12,"
        "13,14,15,16,17,18,"
        "19,20,21,22,23");
    REQUIRE(valid);
}

TEST_CASE("hour_field with every 3 hours is valid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("*/3");
    REQUIRE(valid);
}

TEST_CASE("hour_field with every 3 hours step is valid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("0-23/3");
    REQUIRE(valid);
}

TEST_CASE("hour_field with every 3 hours step begining at 3 is valid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("3/3");
    REQUIRE(valid);
}

TEST_CASE("hour_field with range within list is valid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("0-6,9,12");
    REQUIRE(valid);
}

TEST_CASE("hour_field with multiple ranges within list is valid ", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("0-6,12-18");
    REQUIRE(valid);
}

TEST_CASE("hour_field with unordered list is valid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("3,2,1,5");
    REQUIRE(valid);
}

TEST_CASE("hour_field with excessive range values is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("0-60");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with excessive list values is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("0,60,100");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with 24 is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("24");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with non numeric char is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("?");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with missing range start is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("-23");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with missing range end is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("0-");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with duplicate list values is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("0-5,1,2,3");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with star and value list is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("*,0");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with star range is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("*-*");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with star and value range is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("*-23");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with value and star range is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("0-*");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with descending range is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("23-0");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with empty range is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("-");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with empty list is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate(",");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with empty step is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("/");
    REQUIRE(!valid);
}

TEST_CASE("hour_field with same range values is invalid", "[hour_field]") {
    const hour_field hour;
    bool valid = hour.validate("0-0");
    REQUIRE(!valid);
}
