#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("create current time", "[date_time]") {
	const auto now = date_time::now();
	const auto tp = (system_clock::time_point)now;
	REQUIRE(tp.time_since_epoch().count() > 0);
}

TEST_CASE("1970 is time since epoch 0", "[date_time]") {
	const date_time other(1970, 1, 1);
	const auto tp = (system_clock::time_point)other;
	REQUIRE(tp.time_since_epoch().count() == 0);
}

TEST_CASE("compare date and time properties", "[date_time]") {
	const date_time other(1970, 1, 2, 3, 4, 5);
	REQUIRE(other.year() == 1970);
	REQUIRE(other.month() == 1);
	REQUIRE(other.day() == 2);
	REQUIRE(other.day_of_week() == 5);
	REQUIRE(other.hour() == 3);
	REQUIRE(other.minute() == 4);
	REQUIRE(other.second() == 5);
}

TEST_CASE("3600 seconds since epoch time", "[date_time]") {
	const date_time other(1970, 1, 1, 1);
	auto secondsSinceEpoch = duration_cast<seconds>(((system_clock::time_point)other).time_since_epoch()).count();
	REQUIRE(secondsSinceEpoch == 3600);
}

TEST_CASE("1970-1-3 is weekend", "[date_time]") {
	const date_time other(1970, 1, 3);
	REQUIRE(other.is_weekend());
}

TEST_CASE("1970-1-4 is weekend", "[date_time]") {
	const date_time other(1970, 1, 4);
	REQUIRE(other.is_weekend());
}

TEST_CASE("1970-1-5 is not weekend", "[date_time]") {
	const date_time other(1970, 1, 5);
	REQUIRE(!other.is_weekend());
}

TEST_CASE("1970-1-5 is monday", "[date_time]") {
	const date_time other(1970, 1, 5);
	REQUIRE(other.day_of_week() == 1);
}

TEST_CASE("1970-1-6 is tuesday", "[date_time]") {
	const date_time other(1970, 1, 6);
	REQUIRE(other.day_of_week() == 2);
}

TEST_CASE("1970-1-7 is wednesday", "[date_time]") {
	const date_time other(1970, 1, 7);
	REQUIRE(other.day_of_week() == 3);
}

TEST_CASE("1970-1-8 is thursday", "[date_time]") {
	const date_time other(1970, 1, 8);
	REQUIRE(other.day_of_week() == 4);
}

TEST_CASE("1970-1-9 is friday", "[date_time]") {
	const date_time other(1970, 1, 9);
	REQUIRE(other.day_of_week() == 5);
}

TEST_CASE("1970-1-10 is saturday", "[date_time]") {
	const date_time other(1970, 1, 10);
	REQUIRE(other.day_of_week() == 6);
}

TEST_CASE("1970-1-11 is sunday", "[date_time]") {
	const date_time other(1970, 1, 11);
	REQUIRE(other.day_of_week() == 0);
}

TEST_CASE("compare equal to", "[date_time]") {
	const auto now = date_time::now();
	const auto other = now;
	REQUIRE(now == other);
}

TEST_CASE("compare greater than", "[date_time]") {
	const auto other = date_time(2000,1,1);
	const auto now = date_time::now();
	REQUIRE(now > other);
}

TEST_CASE("compare less then", "[date_time]") {
	const auto other = date_time(2000, 1, 1);
	const auto now = date_time::now();
	REQUIRE(other < now);
}

TEST_CASE("compare greater then or equal to", "[date_time]") {
	const auto other = date_time(date_time::now() - seconds(1));
	const auto now = date_time::now();
	REQUIRE(now >= other);
}

TEST_CASE("compare less then or equal to", "[date_time]") {
	const auto other = date_time(date_time::now() - seconds(1));
	const auto now = date_time::now();
	REQUIRE(other <= other);
}

TEST_CASE("2000 is leap year", "[date_time]") {
	const auto other = date_time(2000, 1, 1);
	REQUIRE(other.is_leap());
}

TEST_CASE("2100 is not leap year", "[date_time]") {
	const auto other = date_time(2100, 1, 1);
	REQUIRE(!other.is_leap());
}

TEST_CASE("jan has 31 days", "[date_time]") {
	const auto other = date_time(2000, 1, 31);
	REQUIRE(other.last_day_of_month() == 31);
	REQUIRE(other.day() == 31);
}

TEST_CASE("feb within leap year has 29 days", "[date_time]") {
	const auto other = date_time(2000, 2, 29);
	REQUIRE(other.last_day_of_month() == 29);
	REQUIRE(other.day() == 29);
}

TEST_CASE("feb within non leap year has 28 days", "[date_time]") {
	const auto other = date_time(2001, 2, 28);
	REQUIRE(other.last_day_of_month() == 28);
	REQUIRE(other.day() == 28);
}

TEST_CASE("mar has 31 days", "[date_time]") {
	const auto other = date_time(2000, 3, 31);
	REQUIRE(other.last_day_of_month() == 31);
	REQUIRE(other.day() == 31);
}

TEST_CASE("apr has 30 days", "[date_time]") {
	const auto other = date_time(2000, 4, 30);
	REQUIRE(other.last_day_of_month() == 30);
	REQUIRE(other.day() == 30);
}

TEST_CASE("may has 31 days", "[date_time]") {
	const auto other = date_time(2000, 5, 31);
	REQUIRE(other.last_day_of_month() == 31);
	REQUIRE(other.day() == 31);
}

TEST_CASE("jun has 30 days", "[date_time]") {
	const auto other = date_time(2000, 6, 30);
	REQUIRE(other.last_day_of_month() == 30);
	REQUIRE(other.day() == 30);
}

TEST_CASE("jul has 31 days", "[date_time]") {
	const auto other = date_time(2000, 7, 31);
	REQUIRE(other.last_day_of_month() == 31);
	REQUIRE(other.day() == 31);
}

TEST_CASE("aug has 31 days", "[date_time]") {
	const auto other = date_time(2000, 8, 31);
	REQUIRE(other.last_day_of_month() == 31);
	REQUIRE(other.day() == 31);
}

TEST_CASE("sep has 30 days", "[date_time]") {
	const auto other = date_time(2000, 9, 30);
	REQUIRE(other.last_day_of_month() == 30);
	REQUIRE(other.day() == 30);
}

TEST_CASE("oct has 31 days", "[date_time]") {
	const auto other = date_time(2000, 10, 31);
	REQUIRE(other.last_day_of_month() == 31);
	REQUIRE(other.day() == 31);
}

TEST_CASE("nov has 30 days", "[date_time]") {
	const auto other = date_time(2000, 11, 30);
	REQUIRE(other.last_day_of_month() == 30);
	REQUIRE(other.day() == 30);
}

TEST_CASE("dec has 31 days", "[date_time]") {
	const auto other = date_time(2000, 12, 31);
	REQUIRE(other.last_day_of_month() == 31);
	REQUIRE(other.day() == 31);
}

TEST_CASE("throw if year is invalid", "[date_time]") {
	REQUIRE_THROWS_AS(date_time(1969, 1, 1), invalid_argument);
	REQUIRE_THROWS_AS(date_time(5138, 1, 1), invalid_argument);
}

TEST_CASE("throw if month is invalid", "[date_time]") {
	REQUIRE_THROWS_AS(date_time(2000, 0, 1), invalid_argument);
	REQUIRE_THROWS_AS(date_time(2000, 13, 1), invalid_argument);
}

TEST_CASE("throw if day is invalid", "[date_time]") {
	REQUIRE_THROWS_AS(date_time(2000, 1, 0), invalid_argument);
	REQUIRE_THROWS_AS(date_time(2000, 1, 32), invalid_argument);
}

TEST_CASE("throw if hour is invalid", "[date_time]") {
	REQUIRE_THROWS_AS(date_time(2000, 1, 1, -1), invalid_argument);
	REQUIRE_THROWS_AS(date_time(2000, 1, 1, 24), invalid_argument);
}

TEST_CASE("throw if minute is invalid", "[date_time]") {
	REQUIRE_THROWS_AS(date_time(2000, 1, 1, 0, -1), invalid_argument);
	REQUIRE_THROWS_AS(date_time(2000, 1, 1, 0, 60), invalid_argument);
}

TEST_CASE("throw if second is invalid", "[date_time]") {
	REQUIRE_THROWS_AS(date_time(2000, 1, 1, 0, 0, -1), invalid_argument);
	REQUIRE_THROWS_AS(date_time(2000, 1, 1, 0, 0, 60), invalid_argument);
}

TEST_CASE("31 february is 2 march", "[date_time]") {
	const auto other = date_time(2000, 2, 31);
	REQUIRE(other.month() == 3);
	REQUIRE(other.day() == 2);
}

TEST_CASE("time_point is casted to seconds", "[date_time]") {
	const auto now = date_time::now();
	const auto other = now + milliseconds(50);
	REQUIRE(other == now);
}
