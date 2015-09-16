/*
  ==============================================================================

    cardsets.hpp
    Created: 14 Sep 2015 2:09:19pm
    Author:  Bladerunner

  ==============================================================================
*/

#ifndef CARDSETS_HPP_INCLUDED
#define CARDSETS_HPP_INCLUDED

namespace SM	//(sudden magic)
{
namespace dominion  //for all of the code related specifically to the deck-building game Dominion.
{
//An enumeration of all of the sets published in the deck-building game Dominion at the time of this compilation.
enum class cardsets
{
    alchemy
    , base
    , cornucopia
    , dark_ages
    , dominion
    , guilds
    , hinterlands
    , intrigue
    , promo
    , prosperity
    , seaside
};  //end enum class cardsets
}	//end namespace dominion
}	//end namespace SM (sudden magic)

#endif  // CARDSETS_HPP_INCLUDED