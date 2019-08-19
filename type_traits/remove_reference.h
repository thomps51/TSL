#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 26 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::remove_reference

namespace tsl
{
   template <class T>
   struct remove_reference
   {
      using type = T;
   };
   
   template <class T>
   struct remove_reference<T &>
   {
      using type = T;
   };

   template <class T>
   using remove_reference_t = typename remove_reference<T>::type;
}
