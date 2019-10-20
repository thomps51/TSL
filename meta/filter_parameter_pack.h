#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 13 October 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::meta::find_if_not_matching

#include <utility>

namespace tsl { namespace meta { namespace details {
   template <class T, std::size_t MaxIndex, class... Args>
   struct find_if_not_matching_impl;
}}}

namespace tsl { namespace meta {

   /* @brief

    */
   template <class T, class... Args>
   using find_if_not_matching =
      typename details::find_if_not_matching_impl<T, sizeof...(Args) - 1, Args...>::type;
}}

namespace tsl { namespace meta { namespace details {
   template <class T, std::size_t MaxIndex, class Arg>
   struct find_if_not_matching_impl<T, MaxIndex, Arg>
   {
      using type = std::conditional_t
      <
         std::is_same_v<T, std::decay_t<Arg>>
         , std::index_sequence<>
         , std::index_sequence<MaxIndex>
      >;
   };

   template <size_t Index, class Sequence>
   struct prepend_index_sequence;

   template <size_t Index, size_t... Indices>
   struct prepend_index_sequence<Index, std::index_sequence<Indices...>>
   {
      using type = std::index_sequence<Index, Indices...>;
   };

   template <class T, std::size_t MaxIndex, class Arg, class... Args>
   struct find_if_not_matching_impl<T, MaxIndex, Arg, Args...>
   {
      static size_t const index = MaxIndex - sizeof...(Args);

      using recursive_case = typename find_if_not_matching_impl<T, MaxIndex, Args...>::type;

      using type = std::conditional_t
      <
         std::is_same_v<T, std::decay_t<Arg>>
         , recursive_case
         , typename prepend_index_sequence<index, recursive_case>::type
      >;
   };
}}}
