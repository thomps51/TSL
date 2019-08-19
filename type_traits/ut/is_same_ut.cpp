#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 20 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <catch2/catch.hpp>
#include "../is_same.h"

using tsl::is_same;

namespace
{
    struct test_struct
    {
    };
}

TEMPLATE_TEST_CASE("Test tsl::is_same", "[is_same][template]", bool, test_struct, char)
{
   REQUIRE(is_same<TestType, TestType>::value == true);
   REQUIRE(is_same<TestType const, TestType>::value == false);
   REQUIRE(is_same<TestType const &, TestType>::value == false);
   REQUIRE(is_same<TestType, TestType const>::value == false);
   REQUIRE(is_same<TestType, TestType const &>::value == false);

   REQUIRE(is_same<volatile TestType, TestType>::value == false);
   REQUIRE(is_same<volatile TestType const, TestType>::value == false);
   REQUIRE(is_same<volatile TestType const &, TestType>::value == false);
   REQUIRE(is_same<TestType, volatile TestType>::value == false);

   REQUIRE(is_same<TestType, int>::value == false);
   REQUIRE(is_same<TestType, void>::value == false);
}
