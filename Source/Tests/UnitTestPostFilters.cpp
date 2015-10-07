/*
  ==============================================================================

    UnitTestPostFilters.cpp
    Created: 6 Oct 2015 4:11:17pm
    Author:  caps

  ==============================================================================
*/

#include "UnitTestPostFilters.hpp"

#include "../Source/CardShuffler.hpp"

#include "../Source/cardsets.hpp"
#include "../Source/cardtypes.hpp"

namespace SM
{
auto UnitTestPostFilters::runTest() -> void
{
    beginTest("Beginning post filter cardset max testing");

    using sets = Dominion::Cardsets;

    expect(shuf->getMax(sets::alchemy) >= 10
           , "default max for a cardset is less than 10");

    shuf->setMax(sets::alchemy, 2);

    expect(shuf->getMax(sets::alchemy) == 2
           , "max on a cardset not correctly set");

    beginTest("Beginning post filter cardset min testing");
    expect(shuf->getMin(sets::alchemy) == 0
           , "default min for a cardset is not ZERO");

    shuf->setMin(sets::alchemy, 2);

    expect(shuf->getMin(sets::alchemy) == 2
           , "min on a cardset not correctly set");

    beginTest("Beginning post filter cardtype max testing");

    using types = Dominion::Cardtypes;
    expect(shuf->getMax(types::action) >= 10
           , "default max for a cardtype is less than 10");

    shuf->setMax(types::action, 4);
    expect(shuf->getMax(types::action) == 4
           , "max on a cardtype not correctly set");

    beginTest("Beginning post filter cardtype min testing");

    expect(shuf->getMin(types::action) == 0
           , "default min for a cardtype is not ZERO");

    shuf->setMin(types::action, 4);
    expect(shuf->getMin(types::action) == 4
           , "min on a cardtype not correctly set");
}
}   //end namespace SM