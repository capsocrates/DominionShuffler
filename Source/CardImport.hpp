#ifndef CARD_IMPORT_HPP_INCLUDED
#define CARD_IMPORT_HPP_INCLUDED

/*
  ==============================================================================

    CardImport.hpp
    Created: 14 Sep 2015 11:45:07am
    Author:  Bladerunner

  ==============================================================================
*/

#include <vector>

namespace SM	//(sudden magic)
{
namespace Dominion  //for all of the code related specifically to the deck-building game Dominion.
{

class RandomizerCard;

//TODO write code to read card files into card class
std::vector<RandomizerCard> read_cards();

}	//end namespace dominion
}	//end namespace SM (sudden magic)

#endif  // CARD_IMPORT_HPP_INCLUDED