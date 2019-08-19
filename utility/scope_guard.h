#pragma once
#ifndef included_tsl_utility_scope_guard_02December2018_
#define included_tsl_utility_scope_guard_02December2018_

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 02 December 2018

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::utility::scope_guard

namespace tsl::utility
{
    template <class Callable>
    class scope_guard
    {
    public:
        ~scope_guard();

        scope_guard(Callable && _callable);

    private:
        Callable callable_;
    };
}

namespace tsl::utility
{
    //**********************************************************************************************
    // Notes:
    //----------------------------------------------------------------------------------------------
    template <class Callable>
    scope_guard<Callable>::scope_guard(Callable && _callable)
        : callable_(std::move(_callable))
    {

    }

    //**********************************************************************************************
    // Notes:
    //----------------------------------------------------------------------------------------------
    template <class Callable>
    scope_guard<Callable>::~scope_guard()
    {
        callable_();
    }
}
#endif
