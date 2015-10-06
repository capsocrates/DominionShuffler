/*
  ==============================================================================

    UnitTestCardtypeFilters.cpp
    Created: 6 Oct 2015 4:05:28pm
    Author:  caps

  ==============================================================================
*/

#include "UnitTestCardtypeFilters.hpp"

#include "../Source/CardShuffler.hpp"

#include "../Cardtypes.hpp"

namespace SM
{
auto UnitTestCardtypeFilters::runTest() -> void
{
    beginTest("Beginning cardtype disable testing");
    using types = Dominion::Cardtypes;
    shuf->disableCardtype(types::action);

    expect(!shuf->cardtypeEnabled(types::action)
           , "disabling a single cardtype does not work");

    shuf->disableCardtype(types::attack);

    expect(!shuf->cardtypeEnabled(types::action)
           , "disabling a second cardtype re-enables a previously disabled cardtype");
    expect(!shuf->cardtypeEnabled(types::attack)
           , "disabling a second cardtype does not work");

    beginTest("Beginning cardtype enable testing");
    shuf->enableCardtype(types::action);

    expect(!shuf->cardtypeEnabled(types::attack)
           , "re-enabling a previously disabled cardtype also enables an unrelated cardtype");
    expect(shuf->cardtypeEnabled(types::action)
           , "re-enabling a previously disabled cardtype does not work");
}
}   //end namespace SM