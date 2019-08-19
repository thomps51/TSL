#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 21 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::array_size

namespace tsl
{
   template <class T>
   struct array_size
   {
      static unsigned const value = 0u;
   };

   template <class T, unsigned N>
   struct array_size<T[N]>
   {
      static unsigned const value = N;
   };

   template <class T>
   inline constexpr unsigned array_size_v = array_size<T>::value;
}

