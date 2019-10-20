#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 20 October 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <type_traits>
#include <catch2/catch.hpp>
#include "../filter_parameter_pack.h"
#include <iostream>

template <class ...>
struct what_type;
 
template <size_t...>
struct what_indices;

namespace {
   template <class...>
   struct types{};

   struct filter_me_out_t {};

   filter_me_out_t filter_me_out;

   template <class... Args, size_t... Indices>
   auto
   call_test_function(std::tuple<Args...> const & _args, std::index_sequence<Indices...>)
   {
      return types<std::tuple_element_t<Indices, std::tuple<Args...>>...>{};
   }

   template <class... Args>
   auto
   test_filter(Args &&... _args)
   {
      using filter = tsl::meta::find_if_not_matching<filter_me_out_t, Args...>;
      return call_test_function(std::forward_as_tuple(_args...), filter());
   }


}

TEST_CASE("test tsl::meta::find_if_not_matching", "[find_if_not_matching]") 
{
   using expected = types<int &, long &, long &>;
   //what_type<decltype(test_filter(0, filter_me_out, 6l, 8l))> t{};
   static_assert(std::is_same_v<expected, decltype(test_filter(0, filter_me_out, 6l, 8l))>);
}
