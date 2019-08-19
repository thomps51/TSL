#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 27 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <catch2/catch.hpp>
#include "../enable_if.h"
#include "../is_same.h"

using tsl::enable_if_t;
using tsl::is_same_v;

template <class T, class U = void>
struct myClass
{
   static bool const value = false;
};

template <class T>
struct myClass<T, enable_if_t<is_same_v<T, int>>>
{
   static bool const value = true;
};

template <class T>
struct myClass<T, enable_if_t<is_same_v<T, long>>>
{
   static bool const value = true;
};

TEST_CASE("Test tsl::enable_if", "[enable_if]") 
{
   REQUIRE(myClass<int>::value == true);
   REQUIRE(myClass<long>::value == true);
   REQUIRE(myClass<char>::value == false);
}
