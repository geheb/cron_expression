#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "minute_field.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("range start", "[minute_field]") {
	const minute_field minute;
	REQUIRE(minute.range_start() == 0);
}

TEST_CASE("range end", "[minute_field]") {
	const minute_field minute;
	REQUIRE(minute.range_end() == 59);
}

TEST_CASE("position", "[minute_field]") {
	const minute_field minute;
	REQUIRE(minute.pos() == cron_field_pos::minute);
}

TEST_CASE("unique minute", "[minute_field]") {
	const minute_field minute;
	for (int i = 0; i < 60; i++)
	{
		bool valid = minute.validate(std::to_string(i));
		REQUIRE(valid);
	}
}

TEST_CASE("every minute", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("*");
	REQUIRE(valid);
}

TEST_CASE("every minute via step", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("*/1");
	REQUIRE(valid);
}

TEST_CASE("every minute via range", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("0-59");
	REQUIRE(valid);
}

TEST_CASE("every minute via list", "[minute_field]") {
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

TEST_CASE("every 5 minutes via step", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("*/5");
	REQUIRE(valid);
}

TEST_CASE("every 5 minutes via range step", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("0-59/5");
	REQUIRE(valid);
}

TEST_CASE("every 5 minutes from 0", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("0/5");
	REQUIRE(valid);
}

TEST_CASE("every 5 minutes via list", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("0,5,10,15,20,25,30,35,40,45,50,55");
	REQUIRE(valid);
}

TEST_CASE("every minute from 0-15 then at 30 and 45 minute", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("0-15,39,45");
	REQUIRE(valid);
}

TEST_CASE("every minute from 0-15 then from 30-45 ", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("0-15,30-45");
	REQUIRE(valid);
}

TEST_CASE("at minute 3, 2, and 1", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("3,2,1");
	REQUIRE(valid);
}

TEST_CASE("range from 0 to 100", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("0-100");
	REQUIRE(!valid);
}

TEST_CASE("at minute 0, 60 and 100", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("0,60,100");
	REQUIRE(!valid);
}

TEST_CASE("at minute 60", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("60");
	REQUIRE(!valid);
}

TEST_CASE("non numeric char", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("?");
	REQUIRE(!valid);
}

TEST_CASE("missing start range", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("-1");
	REQUIRE(!valid);
}

TEST_CASE("missing end range", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("1-");
	REQUIRE(!valid);
}

TEST_CASE("duplicate values via list", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("1,2,3,1");
	REQUIRE(!valid);
}

TEST_CASE("duplicate values via range and list", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("1-15,10");
	REQUIRE(!valid);
}

TEST_CASE("every minute and at minute 0", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("*,0");
	REQUIRE(!valid);
}

TEST_CASE("star range", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("*-*");
	REQUIRE(!valid);
}

TEST_CASE("start range with star", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("*-59");
	REQUIRE(!valid);
}

TEST_CASE("end range with star", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("1-*");
	REQUIRE(!valid);
}

TEST_CASE("every minute from 30 to 10", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("30-10");
	REQUIRE(!valid);
}

TEST_CASE("missing range", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("-");
	REQUIRE(!valid);
}

TEST_CASE("equal range", "[minute_field]") {
	const minute_field minute;
	bool valid = minute.validate("0-0");
	REQUIRE(!valid);
}
