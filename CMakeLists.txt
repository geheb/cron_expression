cmake_minimum_required (VERSION 3.8)

project (cron_expression)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cron_expression "cron_expression.cpp" "cron_expression.h" "cron_field.cpp" "cron_field.h" "date_time.cpp" "date_time.h" "day_of_month_field.cpp" "day_of_month_field.h" "day_of_week_field.cpp" "day_of_week_field.h" "hour_field.cpp" "hour_field.h" "minute_field.cpp" "minute_field.h" "month_field.cpp" "month_field.h")

find_package(Catch2 3 REQUIRED)

add_executable(cron_expression_tests cron_expression_tests.cpp)
target_link_libraries(cron_expression_tests PRIVATE cron_expression Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(cron_expression_tests)

add_executable(date_time_tests date_time_tests.cpp)
target_link_libraries(date_time_tests PRIVATE cron_expression Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(date_time_tests)

add_executable(day_of_month_field_tests day_of_month_field_tests.cpp)
target_link_libraries(day_of_month_field_tests PRIVATE cron_expression Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(day_of_month_field_tests)

add_executable(day_of_week_field_tests day_of_week_field_tests.cpp)
target_link_libraries(day_of_week_field_tests PRIVATE cron_expression Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(day_of_week_field_tests)

add_executable(hour_field_tests hour_field_tests.cpp)
target_link_libraries(hour_field_tests PRIVATE cron_expression Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(hour_field_tests)

add_executable(minute_field_tests minute_field_tests.cpp)
target_link_libraries(minute_field_tests PRIVATE cron_expression Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(minute_field_tests)

add_executable(month_field_tests month_field_tests.cpp)
target_link_libraries(month_field_tests PRIVATE cron_expression Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(month_field_tests)


