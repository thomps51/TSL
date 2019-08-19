#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 27 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <catch2/catch.hpp>
#include "../array_size.h"

using tsl::array_size_v;

#define TEST_ARRAY_SIZE(_type, _expected_size) REQUIRE(array_size_v<_type> == _expected_size)

TEST_CASE("Test tsl::array_size", "[array_size]") 
{
   TEST_ARRAY_SIZE(int, 0);
   TEST_ARRAY_SIZE(int[5], 5);
   TEST_ARRAY_SIZE(int[5][4], 5); // yes, this is how array types are supposed to work
   TEST_ARRAY_SIZE(int[4][5], 4);
   TEST_ARRAY_SIZE(int[1][2][3][4][5], 1);
}
