#ifndef UNITTESTPOSTFILTERS_HPP_INCLUDED
#define UNITTESTPOSTFILTERS_HPP_INCLUDED

/*
  ==============================================================================

    UnitTestPostFilters.hpp
    Created: 6 Oct 2015 4:11:17pm
    Author:  caps

  ==============================================================================
*/

#include "UnitTestShuffleFilters.hpp"

namespace SM
{
class UnitTestPostFilters : public ShuffleFiltersUnitTest
{
public:
    UnitTestPostFilters() : ShuffleFiltersUnitTest("UnitTestPostFilters") {};
    auto runTest() -> void override;
};
}   //end namespace SM

// Creating a static instance will automatically add the instance to the array
// returned by UnitTest::getAllTests(), so the test will be included when you call
// UnitTestRunner::runAllTests()
static SM::UnitTestPostFilters postFilters;

#endif  // UNITTESTPOSTFILTERS_HPP_INCLUDED
