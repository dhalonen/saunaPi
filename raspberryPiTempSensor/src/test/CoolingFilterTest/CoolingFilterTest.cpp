//
// Created by David Halonen on 2/15/21.
//
#include <string>

#include "../include/catch.hpp"

#include "../../main/coolingFilter/CoolingFilter.h"

TEST_CASE("Time & temperature")
{
    time_t rawtime = time(&rawtime);

    CoolingFilter filter;
    REQUIRE(filter.accept(&rawtime,135));
}

TEST_CASE("Non-standard initial values")
{
    time_t rawtime = time(&rawtime);
    CoolingFilter ninetyFilter(6, 0, true, false);
    REQUIRE(ninetyFilter.accept(&rawtime, 91));
    CoolingFilter disabled(6, 0, false, false);
    REQUIRE_FALSE(disabled.isEnabled());
}

TEST_CASE("In random state")
{
    CoolingFilter filter;
    time_t eveningTime = time(&eveningTime);
    struct tm *evening = localtime(&eveningTime);
    evening->tm_hour = 19;
    evening->tm_min = 30;

    time_t now = mktime(evening);
    REQUIRE(filter.accept(&now,10));

    evening->tm_min += 7;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 9));

    evening->tm_min += 7;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 28));

    evening->tm_min += 7;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 7));

    evening->tm_min += 7;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 46));

    evening->tm_min += 7;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 55));

    evening->tm_min += 7;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 64));

    evening->tm_min += 7;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 73));

    evening->tm_min += 7;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 2));
}

TEST_CASE("In heating state")
{
    CoolingFilter filter;
    time_t eveningTime = time(&eveningTime);
    struct tm *evening = localtime(&eveningTime);
    evening->tm_hour = 19;
    evening->tm_min = 30;

    time_t now = mktime(evening);
    REQUIRE(filter.accept(&now, 10));

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 19));


    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 28));

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 37));

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 46));

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 55));

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 64));

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 73));

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(filter.accept(&now, 2));
}

TEST_CASE("In cooling state")
{
    CoolingFilter isCooling;
    time_t eveningTime = time(&eveningTime);
    struct tm *evening = localtime(&eveningTime);
    evening->tm_hour = 23;
    evening->tm_min = 20;

    time_t now = mktime(evening);
    REQUIRE(isCooling.accept(&now, 10)); //11:20

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(isCooling.accept(&now, 9)); //11:26

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(isCooling.accept(&now, 8)); //11:32

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(isCooling.accept(&now, 7)); //11:38

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(isCooling.accept(&now, 6)); //11:44

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(isCooling.accept(&now, 5)); //11:50

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE(isCooling.accept(&now, 4)); //11:56

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE_FALSE(isCooling.accept(&now, 3)); //12:02

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE_FALSE(isCooling.accept(&now, 2));

    evening->tm_min += 6;
    now = mktime(evening);
    REQUIRE_FALSE(isCooling.accept(&now, 1));
}

TEST_CASE("Enabled / Disabled test")
{
    CoolingFilter enabled;
    REQUIRE(enabled.isEnabled());
    enabled.disable();
    REQUIRE_FALSE(enabled.isEnabled());
    CoolingFilter disabled(6, 0, false);
    REQUIRE_FALSE(disabled.isEnabled());
    disabled.enable();
    REQUIRE(disabled.isEnabled());
}

