#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 27 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <catch2/catch.hpp>
#include "../conditional.h"
#include "../is_same.h"

using tsl::conditional_t;
using tsl::is_same_v;

#define TEST_CONDITIONAL(_bool, _type1, _type2, _expected)                                         \
   REQUIRE(is_same_v<conditional_t<_bool, _type1, _type2>, _expected>)

TEST_CASE("Test tsl::conditional", "[conditional]") 
{
   TEST_CONDITIONAL(true, int, char, int);
   TEST_CONDITIONAL(false, int, char, char);
}
