#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 27 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <catch2/catch.hpp>
#include "../is_reference.h"

using tsl::is_reference_v;

TEST_CASE("Test tsl::is_reference", "[is_reference]") 
{
   REQUIRE(is_reference_v<int &>);
   REQUIRE(is_reference_v<long &>);
   REQUIRE(is_reference_v<int(&)(char &)>); // this matches std::is_reference's behavior
   REQUIRE(!is_reference_v<long>);
   REQUIRE(!is_reference_v<long *>);
}
