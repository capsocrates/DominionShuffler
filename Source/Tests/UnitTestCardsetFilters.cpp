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
    shuf->disableCardset(sets::dominion);

    expect(!shuf->cardsetEnabled(sets::dominion)
           , "disabling a single cardset does not work");

    shuf->disableCardset(sets::prosperity);

    expect(!shuf->cardsetEnabled(sets::dominion)
           , "disabling a second cardset re-enables a previously disabled cardset");
    expect(!shuf->cardsetEnabled(sets::prosperity)
           , "disabling a second cardset does not work");

    beginTest("Beginning cardset enable testing");
    shuf->enableCardset(sets::dominion);

    expect(!shuf->cardsetEnabled(sets::prosperity)
           , "re-enabling a previously disabled cardset also enables an unrelated cardset");
    expect(shuf->cardsetEnabled(sets::dominion)
           , "re-enabling a previously disabled cardset does not work");
}
}   //end namespace SM