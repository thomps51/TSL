#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 19 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::is_same

#include "integral_constant.h"

namespace tsl
{
    template <class T, class U>
    struct is_same : false_type
    {
    };

    template <class T>
    struct is_same<T, T> : true_type
    {
    };

    template <class T, class U>
    inline constexpr bool is_same_v = is_same<T, U>::value;
}
