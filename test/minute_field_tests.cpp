#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "minute_field.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("minute_field range start is 0", "[minute_field]") {
    const minute_field minute;
    REQUIRE(minute.range_start() == 0);
}

TEST_CASE("minute_field range end is 0", "[minute_field]") {
    const minute_field minute;
    REQUIRE(minute.range_end() == 59);
}

TEST_CASE("minute_field pos is 0", "[minute_field]") {
    const minute_field minute;
    REQUIRE(minute.pos() == cron_field_pos::minute);
}

TEST_CASE("minute_field with specific minute is valid", "[minute_field]") {
    const minute_field minute;
    for (int i = 0; i < 60; i++)
    {
        bool valid = minute.validate(std::to_string(i));
        REQUIRE(valid);
    }
}

TEST_CASE("minute_field with every minute is valid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("*");
    REQUIRE(valid);
}

TEST_CASE("minute_field with every minute step is valid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("*/1");
    REQUIRE(valid);
}

TEST_CASE("minute_field with every minute range is valid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("0-59");
    REQUIRE(valid);
}

TEST_CASE("minute_field with every minute list is valid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate(
        "0,1,2,3,4,5,6,7,8,9,"
        "10,11,12,13,14,15,16,17,18,19,"
        "20,21,22,23,24,25,26,27,28,29,"
        "30,31,32,33,34,35,36,37,38,39,"
        "40,41,42,43,44,45,46,47,48,49,"
        "50,51,52,53,54,55,56,57,58,59");
    REQUIRE(valid);
}

TEST_CASE("minute_field with every 5 minutes is valid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("*/5");
    REQUIRE(valid);
}

TEST_CASE("minute_field with every 5 minutes step is valid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("0-59/5");
    REQUIRE(valid);
}

TEST_CASE("minute_field with every 5 minutes range begining at 5 is valid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("5/5");
    REQUIRE(valid);
}

TEST_CASE("minute_field with range within list is valid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("0-15,39,45");
    REQUIRE(valid);
}

TEST_CASE("minute_field with multiple ranges within list is valid ", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("0-15,30-45");
    REQUIRE(valid);
}

TEST_CASE("minute_field with unordered list is valid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("3,2,1,5");
    REQUIRE(valid);
}

TEST_CASE("minute_field with excessive range values is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("0-100");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with excessive list values is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("0,60,100");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with 60 is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("60");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with non numeric char is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("?");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with missing range start is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("-59");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with missing range end is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("1-");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with duplicate list values is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("1-5,1,2,3");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with star and value list is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("*,0");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with star range is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("*-*");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with star and value range is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("*-59");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with value and star range is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("1-*");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with descending range is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("59-0");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with empty range is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("-");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with empty list is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate(",");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with empty step is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("/");
    REQUIRE(!valid);
}

TEST_CASE("minute_field with same range values is invalid", "[minute_field]") {
    const minute_field minute;
    bool valid = minute.validate("0-0");
    REQUIRE(!valid);
}
