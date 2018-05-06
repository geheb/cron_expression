#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "day_of_week_field.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("day_of_week_field range start is 0", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(wday.range_start() == 0);
}

TEST_CASE("day_of_week_field range end is 6", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(wday.range_end() == 6);
}

TEST_CASE("day_of_week_field pos is 4", "[day_of_week_field]") {
    const day_of_week_field wday;
    REQUIRE(wday.pos() == cron_field_pos::day_of_week);
}

TEST_CASE("day_of_week_field with specific month is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    for (int i = 0; i < 6; i++)
    {
        bool valid = wday.validate(std::to_string(i));
        REQUIRE(valid);
    }
}

TEST_CASE("day_of_week_field with named specific month is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    const char* months[7] = { "SUN",  "MON", "TUE", "WED", "THU", "FRI", "SAT" };
    for (const char* m : months)
    {
        bool valid = wday.validate(m);
        REQUIRE(valid);
    }
}

TEST_CASE("day_of_week_field with every day of week is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("*");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with every day of week step is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("*/1");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with every day of week range is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("0-6");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with named every month range is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("SUN-SAT");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with every day of week list is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("0,1,2,3,4,5,6");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with named every day of week list is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("SUN,MON,TUE,WED,THU,FRI,SAT");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with every 2nd day of week is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("*/2");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with every 2nd day of week within range is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("0-6/2");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with named every 2nd day of week within range is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("SUN-SAT/2");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with every 2nd day of week step begining at 2 is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("2/2");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with every 2nd day of week step begining at tuesday is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("TUE/2");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with range within list is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("0-3,5,6");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with named backward range within list is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("FRI-TUE,3,4");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with multiple ranges within list is valid ", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("0-3,5-6");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with unordered list is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("3,2,1,5");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with the nth day of the week of every month is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 1; j < 6; j++)
        {
            bool valid = wday.validate(to_string(i) + "#" + to_string(j));
            REQUIRE(valid);
        }
    }
}

TEST_CASE("day_of_week_field with sixth monday of every month is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("0#6");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with first unknown day of every month is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("7#1");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with the last day of week of every month", "[day_of_week_field]") {
    const day_of_week_field wday;
    for (int i = 0; i < 7; i++)
    {
        bool valid = wday.validate(to_string(i) + "L");
        REQUIRE(valid);
    }
}

TEST_CASE("day_of_week_field with current day of week is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("?");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with excessive range values is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("1-60");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with excessive list values is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("1,60,100");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with day of week 7 is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("7");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with non numeric char is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("L");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with missing range start is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("-6");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with missing range end is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("0-");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with duplicate list values is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("0-5,1,2,3");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with star and value list is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("*,0");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with star range is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("*-*");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with star and value range is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("*-6");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with value and star range is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("0-*");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with descending range is valid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("6-0");
    REQUIRE(valid);
}

TEST_CASE("day_of_week_field with empty range is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("-");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with empty list is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate(",");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with empty step is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("/");
    REQUIRE(!valid);
}

TEST_CASE("day_of_week_field with same range values is invalid", "[day_of_week_field]") {
    const day_of_week_field wday;
    bool valid = wday.validate("0-0");
    REQUIRE(!valid);
}
