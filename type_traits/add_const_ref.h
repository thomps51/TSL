#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 19 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::add_const_ref

namespace tsl
{
    template <class T>
    struct add_const_ref
    {
        typedef T const & type;
    };

    template <class T>
    struct add_const_ref<T const &>
    {
        typedef T const & type;
    };
}
