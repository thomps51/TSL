#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 18 August 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <type_traits>
#include <catch2/catch.hpp>
#include "../map.h"
#include <iostream>

using tsl::meta::make_map;
using tsl::meta::make_pair;

template <class ...>
struct what_type;

struct my_type;

struct my_handler
{
   template <class KeyType, class ValueType>
   void
   on_value(ValueType _value)
   {
      if constexpr(std::is_same_v<int, KeyType>)
      {
         std::cout << _value << std::endl;
      }
   }
};

TEST_CASE("test tsl::meta::map", "[map]") 
{
   using namespace std::literals;
   auto constexpr my_map = make_map(
      make_pair<int>("int")
      , make_pair<double>("double")
      , make_pair<unsigned>(1)
      , make_pair<my_type>("my_type")
      , make_pair<long>("long"));
   
   static_assert(std::is_same_v<int, my_map::find("int")>);

   static_assert(std::is_same_v<int,      TSL_META_FIND_TYPE(my_map, "int")>);
   static_assert(std::is_same_v<double,   TSL_META_FIND_TYPE(my_map, "double")>);
   static_assert(std::is_same_v<long,     TSL_META_FIND_TYPE(my_map, "long")>);
   static_assert(std::is_same_v<my_type,  TSL_META_FIND_TYPE(my_map, "my_type")>);
   static_assert(std::is_same_v<unsigned, TSL_META_FIND_TYPE(my_map, 1)>);

   my_handler handler;
   my_map.enumerate(handler);
   
   static_assert("int"sv     == my_map.find<int>());
   static_assert("double"sv  == my_map.find<double>());
   static_assert(1           == my_map.find<unsigned>());
   static_assert("my_type"sv == my_map.find<my_type>());
   static_assert("long"sv    == my_map.find<long>());
}
