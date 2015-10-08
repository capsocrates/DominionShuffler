/*
  ==============================================================================

    UnitTestShuffleFilters.cpp
    Created: 6 Oct 2015 3:05:39pm
    Author:  caps

  ==============================================================================
*/

#include "UnitTestShuffleFilters.hpp"

#include "../Source/CardShuffler.hpp"

#include "sm/utility_make_unique.hpp"

namespace SM
{
auto ShuffleFiltersUnitTest::initialise() -> void
{
    shuf = SM::utility::make_unique<Dominion::CardShuffler>();
}
}   //end namespace SM