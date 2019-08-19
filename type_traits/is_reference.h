#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 26 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::is_reference

#include "integral_constant.h"

namespace tsl
{
   template <class T>
   struct is_reference : false_type
   {
   };

   template <class T>
   struct is_reference<T &> : true_type
   {
   };
   
   template <class T>
   inline constexpr bool is_reference_v = is_reference<T>::value;
}
