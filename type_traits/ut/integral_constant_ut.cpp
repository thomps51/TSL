#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 27 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <catch2/catch.hpp>
#include "../integral_constant.h"
#include "../is_same.h"

using tsl::integral_constant_v;
using tsl::integral_constant;

TEST_CASE("Test tsl::integral_constant", "[integral_constant]") 
{
   REQUIRE(integral_constant_v<char, 'c'> == 'c');
   REQUIRE(integral_constant_v<bool, true> == true);
   REQUIRE(integral_constant_v<int, 5> == 5);
   REQUIRE(integral_constant<int, 5>() == 5);
   REQUIRE(static_cast<int>(integral_constant<int, 5>()) == 5);
}
