#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "month_field.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("month_field: configuration is valid", "[month_field]") {
    const month_field month;
    REQUIRE(month.range_start() == 1);
    REQUIRE(month.range_end() == 12);
    REQUIRE(month.pos() == cron_field_pos::month);
}

TEST_CASE("month_field: value 1-12 is valid", "[month_field]") {
    const month_field month;
    for (int i = 1; i < 13; i++) {
        REQUIRE(month.validate(std::to_string(i)));
    }
}

TEST_CASE("month_field: value JAN-DEC is valid", "[month_field]") {
    const month_field month;
    const char* months[12] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };
    for (const char* m : months) {
        REQUIRE(month.validate(m));
    }
}

TEST_CASE("month_field: value 1-12 matches date_time", "[month_field]") {
    const month_field month;
    for (int i = 1; i < 13; i++) {
        REQUIRE(month.match(to_string(i), date_time(2018, i, 1)));
    }
}

TEST_CASE("month_field: pattern every month is valid", "[month_field]") {
    const month_field month;
    REQUIRE(month.validate("*"));
    REQUIRE(month.validate("*/1"));
    REQUIRE(month.validate("1/1"));
    REQUIRE(month.validate("1-12/1"));
    REQUIRE(month.validate("1-12"));
    REQUIRE(month.validate(
        "1,2,3,4,5,6,"
        "7,8,9,10,11,12"));
    REQUIRE(month.validate(
        "JAN,FEB,MAR,APR,MAY,JUN,"
        "JUL,AUG,SEP,OCT,NOV,DEC"));
    REQUIRE(month.validate("JAN-DEC"));
    REQUIRE(month.validate("DEC-NOV"));
}

TEST_CASE("month_field: pattern every month matches current time", "[month_field]") {
    const month_field month;
    REQUIRE(month.match("*", date_time::now()));
    REQUIRE(month.match("*/1", date_time::now()));
    REQUIRE(month.match("1/1", date_time::now()));
    REQUIRE(month.match("1-12/1", date_time::now()));
    REQUIRE(month.match("1-12", date_time::now()));
    REQUIRE(month.match(
        "1,2,3,4,5,6,"
        "7,8,9,10,11,12", date_time::now()));
    REQUIRE(month.match(
        "JAN,FEB,MAR,APR,MAY,JUN,"
        "JUL,AUG,SEP,OCT,NOV,DEC", date_time::now()));
    REQUIRE(month.match("JAN-DEC", date_time::now()));
    REQUIRE(month.match("DEC-NOV", date_time::now()));
}

TEST_CASE("month_field: pattern every 5 months is valid", "[month_field]") {
    const month_field month;
    REQUIRE(month.validate("*/5"));
    REQUIRE(month.validate("1/5"));
    REQUIRE(month.validate("JAN/5"));
    REQUIRE(month.validate("1-12/5"));
    REQUIRE(month.validate("JAN-DEC/5"));
    REQUIRE(month.validate("1,6,11"));
    REQUIRE(month.validate("1,6,NOV"));
}

TEST_CASE("month_field: pattern every 5 months matches date_time", "[month_field]") {
    const month_field month;
    for (int i = 1; i < 13; i += 5) {
        const auto time = date_time(2018, i, 1);
        REQUIRE(month.match("*/5", time));
        REQUIRE(month.match("1/5", time));
        REQUIRE(month.match("JAN/5", time));
        REQUIRE(month.match("1-12/5", time));
        REQUIRE(month.match("JAN-DEC/5", time));
        REQUIRE(month.match("1,6,11", time));
        REQUIRE(month.match("1,6,NOV", time));
    }
}

TEST_CASE("month_field: list and range values are valid", "[month_field]") {
    const month_field month;
    REQUIRE(month.validate("1"));
    REQUIRE(month.validate("1-6,7,8"));
    REQUIRE(month.validate("1-3,6-9"));
    REQUIRE(month.validate("3,2,1"));
    REQUIRE(month.validate("DEC-MAR"));
    REQUIRE(month.validate("2-1/11"));
}

TEST_CASE("month_field: out of range values are invalid", "[month_field]") {
    const month_field month;
    REQUIRE(!month.validate("0"));
    REQUIRE(!month.validate("13"));
    REQUIRE(!month.validate("120"));
}

TEST_CASE("month_field: range values are invalid", "[month_field]") {
    const month_field month;
    REQUIRE(!month.validate("-"));
    REQUIRE(!month.validate("*-"));
    REQUIRE(!month.validate("*-1"));
    REQUIRE(!month.validate("-*"));
    REQUIRE(!month.validate("1-*"));
    REQUIRE(!month.validate("*-*"));
    REQUIRE(!month.validate("0-0"));
    REQUIRE(!month.validate("0-12"));
    REQUIRE(!month.validate("12-0"));
    REQUIRE(!month.validate("1-"));
    REQUIRE(!month.validate("1-13"));
    REQUIRE(!month.validate("1-?"));
    REQUIRE(!month.validate("?-1"));
    REQUIRE(!month.validate("?-?"));
    REQUIRE(!month.validate("-12"));
}

TEST_CASE("month_field: step values are invalid", "[month_field]") {
    const month_field month;
    REQUIRE(!month.validate("/"));
    REQUIRE(!month.validate("*/*"));
    REQUIRE(!month.validate("/*"));
    REQUIRE(!month.validate("*/"));
    REQUIRE(!month.validate("*/0"));
    REQUIRE(!month.validate("/0"));
    REQUIRE(!month.validate("0/0"));
    REQUIRE(!month.validate("/1-12"));
    REQUIRE(!month.validate("1/1-12"));
    REQUIRE(!month.validate("1-12/0"));
    REQUIRE(!month.validate("0/12"));
    REQUIRE(!month.validate("*/13"));
    REQUIRE(!month.validate("1-1/1"));
    REQUIRE(!month.validate("*/1/1"));
    REQUIRE(!month.validate("1-12/12"));
    REQUIRE(!month.validate("12-1/3"));
    REQUIRE(!month.validate("2-1/12")); 
    REQUIRE(!month.validate("12-11/12"));
}

TEST_CASE("month_field: list values are invalid", "[month_field]") {
    const month_field month;
    REQUIRE(!month.validate(","));
    REQUIRE(!month.validate("*,"));
    REQUIRE(!month.validate(",*"));
    REQUIRE(!month.validate("*,*"));
    REQUIRE(!month.validate("*,1"));
    REQUIRE(!month.validate("1,*"));
    REQUIRE(!month.validate("*/5,*/5"));
    REQUIRE(!month.validate("*/5,*"));
    REQUIRE(!month.validate("1,6,100"));
    REQUIRE(!month.validate("1,2,3,1"));
    REQUIRE(!month.validate(",1"));
    REQUIRE(!month.validate("1,"));
}

TEST_CASE("month_field: non numeric values are invalid", "[month_field]") {
    const month_field month;
    REQUIRE(!month.validate("13"));
    REQUIRE(!month.validate("?"));
    REQUIRE(!month.validate("W"));
    REQUIRE(!month.validate("1W"));
    REQUIRE(!month.validate("L"));
    REQUIRE(!month.validate("1L"));
    REQUIRE(!month.validate("1#1"));
    REQUIRE(!month.validate("MON"));
}
