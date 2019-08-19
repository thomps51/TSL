#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 26 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::enable_if

namespace tsl
{
   template <bool B, class T = void>
   struct enable_if;

   template <class T>
   struct enable_if<true, T>
   {
      using type = T;
   };
   
   template <>
   struct enable_if<true, void>
   {
      using type = void;
   };
   
   template <bool B, class T = void>
   using enable_if_t = typename enable_if<B, T>::type;
}
