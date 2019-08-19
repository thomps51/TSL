#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 27 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <catch2/catch.hpp>
#include "../remove_reference.h"
#include "../is_same.h"

using tsl::remove_reference_t;

#define TEST_RM_REF(_type, _expected) tsl::is_same_v<remove_reference_t<_type>, _expected>

TEST_CASE("Test tsl::remove_reference", "[remove_reference]") 
{
   TEST_RM_REF(int &, int);
   TEST_RM_REF(int, int);
   TEST_RM_REF(int *, int);
   TEST_RM_REF(int * &, int *);
   TEST_RM_REF(int (&)(char &), int (&)(char &));
}
