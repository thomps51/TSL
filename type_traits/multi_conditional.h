#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 21 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::multi_conditional

#include "conditional.h"

namespace tsl
{
   /* @brief
      Variadic metafunction that gives the type of the first expression that evaluates to true, else
      gives the final argument.

      It can be thought of like a function with an if-else chain that returns a value, except this
      operates on types, for instance:
      @code
      if (condition1)
      {
         return value1;
      }
      else if (condition2)
      {
         return value2;
      }
      else
      {
         return value3;
      }
      @endcode

      would be similar to the following written with multi_conditional:
      @code
      typedef typename multi_conditional<
         condition1
         , type1
         , condition2
         , type2
         , type3
      >::type type
      @endcode

      Where @c type would be type1, type2, or type3 depending on the conditions, similar to value1, value2, and value3 in the if-else chain.

      @note The conditions must be given in the form of a class with a ::value member.
      @note All types will be evaluated and must be defined to be something, even if they will never be used.
    */
   template <class...>
   struct multi_conditional;

   template <class... Args>
   using multi_conditional_t = typename multi_conditional<Args...>::type;

   template <class T>
   struct multi_conditional<T>
   {
      typedef T type;
   };

   template <class Value, class T, class... Args>
   struct multi_conditional<Value, T, Args...>
   {
      typedef typename tsl::conditional<Value::value, T, typename multi_conditional<Args...>::type>::type type;
   };
}
