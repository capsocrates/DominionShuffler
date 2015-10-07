/*
  ==============================================================================

    UnitTestCardsetFilters.cpp
    Created: 6 Oct 2015 4:05:17pm
    Author:  caps

  ==============================================================================
*/

#include "UnitTestCardsetFilters.hpp"

#include "../Source/CardShuffler.hpp"

#include "../Cardsets.hpp"

namespace SM
{
auto UnitTestCardsetFilters::runTest() -> void
{
    beginTest("Beginning cardset disable testing");
    using sets = Dominion::Cardsets;
    shuf->disable(sets::dominion);

    expect(!shuf->isEnabled(sets::dominion)
           , "disabling a single cardset does not work");

    shuf->disable(sets::prosperity);

    expect(!shuf->isEnabled(sets::dominion)
           , "disabling a second cardset re-enables a previously disabled cardset");
    expect(!shuf->isEnabled(sets::prosperity)
           , "disabling a second cardset does not work");

    beginTest("Beginning cardset enable testing");
    shuf->enable(sets::dominion);

    expect(!shuf->isEnabled(sets::prosperity)
           , "re-enabling a previously disabled cardset also enables an unrelated cardset");
    expect(shuf->isEnabled(sets::dominion)
           , "re-enabling a previously disabled cardset does not work");
}
}   //end namespace SM