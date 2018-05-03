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

