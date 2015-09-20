#ifndef CARD_IMPORT_HPP_INCLUDED
#define CARD_IMPORT_HPP_INCLUDED

/*
  ==============================================================================

    card_import.hpp
    Created: 14 Sep 2015 11:45:07am
    Author:  Bladerunner

  ==============================================================================
*/

#include <vector>

namespace SM	//(sudden magic)
{
namespace dominion  //for all of the code related specifically to the deck-building game Dominion.
{

class randomizer_card;

//TODO write code to read card files into card class
std::vector<randomizer_card> read_cards();

}	//end namespace dominion
}	//end namespace SM (sudden magic)

#endif  // CARD_IMPORT_HPP_INCLUDED