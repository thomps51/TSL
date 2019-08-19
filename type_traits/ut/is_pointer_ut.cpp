#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 27 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <catch2/catch.hpp>
#include "../is_pointer.h"

using tsl::is_pointer_v;

TEST_CASE("Test tsl::is_pointer", "[is_pointer]") 
{
   REQUIRE(is_pointer_v<int *>);
   REQUIRE(is_pointer_v<long *>);
   REQUIRE(is_pointer_v<int(*)(char &)>);
   REQUIRE(!is_pointer_v<long>);
   REQUIRE(!is_pointer_v<long &>);
}
