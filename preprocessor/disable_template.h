#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 20 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides TSL_DISABLE_TEMPLATE macro

namespace tsl { namespace details {
    template <class ...>
    struct disable
    {
        static bool const value = false;
    };
} }

#define TSL_DISABLE_TEMPLATE(T, msg) \
    static_assert(::tsl::details::disable<T>::value, msg);

