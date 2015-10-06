#ifndef UNITTESTCARDTYPEFILTERS_HPP_INCLUDED
#define UNITTESTCARDTYPEFILTERS_HPP_INCLUDED

/*
  ==============================================================================

    UnitTestCardtypeFilters.h
    Created: 6 Oct 2015 4:05:28pm
    Author:  caps

  ==============================================================================
*/

#include "UnitTestShuffleFilters.hpp"

namespace SM
{
class UnitTestCardtypeFilters : public ShuffleFiltersUnitTest
{
public:
    UnitTestCardtypeFilters() : ShuffleFiltersUnitTest("CardtypeFiltersUnitTest") {};
    auto runTest() -> void override;
};
}   //end namespace SM

// Creating a static instance will automatically add the instance to the array
// returned by UnitTest::getAllTests(), so the test will be included when you call
// UnitTestRunner::runAllTests()
static SM::UnitTestCardtypeFilters cardtypeFilters;

#endif  // UNITTESTCARDTYPEFILTERS_HPP_INCLUDED
