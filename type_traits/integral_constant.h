#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 20 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::integral_constant

namespace tsl {
   template <class T, T _value>
   struct integral_constant
   {
      static T const value = _value;
      typedef T type;
      constexpr operator T() const noexcept { return value; }
      constexpr T operator()() const noexcept { return value; }
   };

   using true_type = integral_constant<bool, true>;
   using false_type = integral_constant<bool, false>;

   template <class T, T _value>
   inline constexpr T integral_constant_v = integral_constant<T, _value>::value;
}
