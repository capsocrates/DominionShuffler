#ifndef UNITTESTCARDSETFILTERS_HPP_INCLUDED
#define UNITTESTCARDSETFILTERS_HPP_INCLUDED

/*
  ==============================================================================

    UnitTestCardsetFilters.h
    Created: 6 Oct 2015 4:05:17pm
    Author:  caps

  ==============================================================================
*/

#include "UnitTestShuffleFilters.hpp"

namespace SM
{
class UnitTestCardsetFilters : public ShuffleFiltersUnitTest
{
public:
    UnitTestCardsetFilters() : ShuffleFiltersUnitTest("CardsetFiltersUnitTest") {};
    auto runTest() -> void override;
};
}   //end namespace SM

// Creating a static instance will automatically add the instance to the array
// returned by UnitTest::getAllTests(), so the test will be included when you call
// UnitTestRunner::runAllTests()
static SM::UnitTestCardsetFilters cardsetFilters;

#endif  // UNITTESTCARDSETFILTERS_HPP_INCLUDED
