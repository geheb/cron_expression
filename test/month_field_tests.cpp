#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "month_field.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("month_field range start is 1", "[month_field]") {
	const month_field month;
	REQUIRE(month.range_start() == 1);
}

TEST_CASE("month_field range end is 12", "[month_field]") {
	const month_field month;
	REQUIRE(month.range_end() == 12);
}

TEST_CASE("month_field pos is 3", "[month_field]") {
	const month_field month;
	REQUIRE(month.pos() == cron_field_pos::month);
}

TEST_CASE("month_field with specific month is valid", "[month_field]") {
	const month_field month;
	for (int i = 1; i < 13; i++)
	{
		bool valid = month.validate(std::to_string(i));
		REQUIRE(valid);
	}
}

TEST_CASE("month_field with named specific month is valid", "[month_field]") {
	const month_field month;
	const char* months[12] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };
	for (const char* m : months)
	{
		bool valid = month.validate(m);
		REQUIRE(valid);
	}
}

TEST_CASE("month_field with every month is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("*");
	REQUIRE(valid);
}

TEST_CASE("month_field with every month step is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("*/1");
	REQUIRE(valid);
}

TEST_CASE("month_field with every month range is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("1-12");
	REQUIRE(valid);
}

TEST_CASE("month_field with named every month range is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("JAN-DEC");
	REQUIRE(valid);
}

TEST_CASE("month_field with every month list is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("1,2,3,4,5,6,7,8,9,10,11,12");
	REQUIRE(valid);
}

TEST_CASE("month_field with named every month list is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("JAN,FEB,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC");
	REQUIRE(valid);
}

TEST_CASE("month_field with every 4 months is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("*/4");
	REQUIRE(valid);
}

TEST_CASE("month_field with every 4 months step is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("1-12/4");
	REQUIRE(valid);
}

TEST_CASE("month_field with named every 4 months step is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("JAN-DEC/4");
	REQUIRE(valid);
}

TEST_CASE("month_field with every 4 months step begining at 4 is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("4/4");
	REQUIRE(valid);
}

TEST_CASE("month_field with every 4 months step begining at APR is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("APR/4");
	REQUIRE(valid);
}

TEST_CASE("month_field with range within list is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("1-6,9,12");
	REQUIRE(valid);
}

TEST_CASE("month_field with named range within list is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("JAN-JUN,9,12");
	REQUIRE(valid);
}

TEST_CASE("month_field with multiple ranges within list is valid ", "[month_field]") {
	const month_field month;
	bool valid = month.validate("1-6,7-12");
	REQUIRE(valid);
}

TEST_CASE("month_field with unordered list is valid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("3,2,1,5");
	REQUIRE(valid);
}

TEST_CASE("month_field with excessive range values is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("1-60");
	REQUIRE(!valid);
}

TEST_CASE("month_field with excessive list values is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("1,60,100");
	REQUIRE(!valid);
}

TEST_CASE("month_field with month 13 is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("13");
	REQUIRE(!valid);
}

TEST_CASE("month_field with non numeric char is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("L");
	REQUIRE(!valid);
}

TEST_CASE("month_field with missing range start is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("-12");
	REQUIRE(!valid);
}

TEST_CASE("month_field with missing range end is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("1-");
	REQUIRE(!valid);
}

TEST_CASE("month_field with duplicate list values is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("1-5,1,2,3");
	REQUIRE(!valid);
}

TEST_CASE("month_field with star and value list is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("*,0");
	REQUIRE(!valid);
}

TEST_CASE("month_field with star range is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("*-*");
	REQUIRE(!valid);
}

TEST_CASE("month_field with star and value range is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("*-12");
	REQUIRE(!valid);
}

TEST_CASE("month_field with value and star range is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("1-*");
	REQUIRE(!valid);
}

TEST_CASE("month_field with descending range is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("12-1");
	REQUIRE(!valid);
}

TEST_CASE("month_field with empty range is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("-");
	REQUIRE(!valid);
}

TEST_CASE("month_field with empty list is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate(",");
	REQUIRE(!valid);
}

TEST_CASE("month_field with empty step is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("/");
	REQUIRE(!valid);
}

TEST_CASE("month_field with same range values is invalid", "[month_field]") {
	const month_field month;
	bool valid = month.validate("0-0");
	REQUIRE(!valid);
}