#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 21 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::conditional

namespace tsl
{
   template <bool Value, class A, class B>
   struct conditional;

   template <bool Value, class A, class B>
   using conditional_t = typename conditional<Value, A, B>::type;
}

namespace tsl
{
   template <class A, class B>
   struct conditional<true, A, B>
   {
      typedef A type;
   };

   template <class A, class B>
   struct conditional<false, A, B>
   {
      typedef B type;
   };
}
