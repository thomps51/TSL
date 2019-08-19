#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 21 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::add_array

namespace tsl
{
   template <unsigned N, class T>
   struct add_array;

   template <unsigned N, class T>
   using add_array_t = typename add_array<N, T>::type;
}

namespace tsl
{
   template <unsigned N, class T>
   struct add_array
   {
      typedef T type[N];
   };
   
   template <unsigned N>
   struct add_array<N, void>
   {
      typedef void type;
   };
}
