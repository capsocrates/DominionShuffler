#ifndef CARDTYPES_HPP_INCLUDED
#define CARDTYPES_HPP_INCLUDED

/*
  ==============================================================================

    cardtypes.hpp
    Created: 14 Sep 2015 2:09:25pm
    Author:  Bladerunner

  ==============================================================================
*/

namespace SM	//(sudden magic)
{
namespace Dominion  //for all of the code related specifically to the deck-building game Dominion.
{
//An enumeration of all possible card types in the deck-building game Dominion at the time of this compilation.
enum class Cardtypes
{
    action
    , attack
    , blank
    , curse
    , duration
    , event
    , looter
    , prize
    , reaction
    , reserve
    , ruins
    , shelter
    , traveler
    , treasure
    , victory
};  //end enum class Cardtypes
}	//end namespace Dominion
}	//end namespace SM (sudden magic)

#endif  // CARDTYPES_HPP_INCLUDED