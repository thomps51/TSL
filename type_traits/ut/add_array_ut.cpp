#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 27 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <vector>
#include <catch2/catch.hpp>
#include "../add_array.h"
#include "../is_same.h"

using tsl::add_array_t;
using tsl::is_same_v;

#define TEST_ADD_ARRAY(_num, _type, _expected)                                                     \
   REQUIRE(is_same_v<add_array_t<_num, _type>, _expected>)

TEST_CASE("Test tsl::add_array", "[add_array]") 
{
   TEST_ADD_ARRAY(5, void, void); // not valid to have array of voids, fail gracefully
   TEST_ADD_ARRAY(5, void * , void * [5]);
   TEST_ADD_ARRAY(5, int, int[5]);
   TEST_ADD_ARRAY(5, std::vector<int>, std::vector<int>[5]);
}
