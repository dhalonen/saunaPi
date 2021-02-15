//
// Created by David Halonen on 2/15/21.
//
#include <string>

#include "../include/catch.hpp"

#include "../../main/coolingFilter/CoolingFilter.h"

TEST_CASE("In random state")
{
    CoolingFilter filter;
    filter.accept(10);
    REQUIRE_FALSE(filter.isCooling());
    filter.accept(9);
    REQUIRE_FALSE(filter.isCooling());
    filter.accept(28);
    filter.accept(7);
    REQUIRE_FALSE(filter.isCooling());
    filter.accept(46);
    filter.accept(55);
    filter.accept(64);
    REQUIRE_FALSE(filter.isCooling());
    filter.accept(73);
    REQUIRE_FALSE(filter.isCooling());
    filter.accept(2);
    REQUIRE_FALSE(filter.isCooling());
}

TEST_CASE("In heating state")
{
    CoolingFilter filter;
    filter.accept(10);
    REQUIRE_FALSE(filter.isCooling());
    filter.accept(19);
    filter.accept(28);
    filter.accept(37);
    filter.accept(46);
    filter.accept(55);
    filter.accept(64);
    REQUIRE_FALSE(filter.isCooling());
    filter.accept(73);
    REQUIRE_FALSE(filter.isCooling());
    filter.accept(2);
    REQUIRE_FALSE(filter.isCooling());
}

TEST_CASE("In cooling state")
{
   CoolingFilter isCooling;
   REQUIRE(isCooling.isCooling());
   CoolingFilter filter;
   filter.accept(10);
   REQUIRE_FALSE(filter.isCooling());
   filter.accept(9);
   filter.accept(8);
   filter.accept(7);
   filter.accept(6);
   filter.accept(5);
   filter.accept(4);
   REQUIRE(filter.isCooling());
   filter.accept(3);
   REQUIRE(filter.isCooling());
   filter.accept(2);
   REQUIRE(filter.isCooling());
}

TEST_CASE("Enabled / Disabled test")
{
    CoolingFilter enabled;
    REQUIRE(enabled.isEnabled());
    enabled.disable();
    REQUIRE_FALSE(enabled.isEnabled());
    CoolingFilter disabled(false);
    REQUIRE_FALSE(disabled.isEnabled());
    disabled.enable();
    REQUIRE(disabled.isEnabled());
}

