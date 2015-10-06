/*
  ==============================================================================

    UnitTestShuffleFilters.cpp
    Created: 6 Oct 2015 3:05:39pm
    Author:  caps

  ==============================================================================
*/

#include "UnitTestShuffleFilters.hpp"

#include "../Source/CardShuffler.hpp"

namespace SM
{
auto ShuffleFiltersUnitTest::initialise() -> void
{
    shuf = std::make_unique<Dominion::CardShuffler>();
}
}   //end namespace SM