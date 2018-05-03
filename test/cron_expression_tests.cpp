#include <stdexcept>
#include "catch.hpp"
#include "date_time.h"
#include "cron_expression.h"

using namespace geheb;
using namespace std;
using namespace std::chrono;

TEST_CASE("cron_expression with every minute is valid", "[cron_expression]") {
	REQUIRE_NOTHROW(cron_expression("* * * * *"));
}
