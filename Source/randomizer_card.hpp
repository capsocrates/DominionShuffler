/*
  ==============================================================================

    randomizer_card.hpp
    Created:        14 Sep 2015 11:44:59am
    Author:         Bladerunner
    Description:    A code representation of randomizer cards for generating play decks in the Dominion deck-building game.

  ==============================================================================
*/

#ifndef RANDOMIZER_CARD_HPP_INCLUDED
#define RANDOMIZER_CARD_HPP_INCLUDED

#include "cardsets.hpp"
#include "cardtypes.hpp"

//stdlib includes
#include <string>
#include <vector>

namespace SM	//(sudden magic)
{
namespace dominion  //for all of the code related specifically to the deck-building game Dominion.
{

//TODO put cardsets and cardtypes into separate headers

//A class representing a single randomizer card in a deck of randomizer cards.
class randomizer_card
{
public:
    cardsets set;   //The set this card belongs to
    std::wstring name;
    //TODO implement costs in terms of boost::optional?
    int gold_cost;  //Might be 0; especially if there is a potion_cost > 0. Some cards may also have special means of being acquired, like the Urchin and Mercenary. These cards will have a cost of 0.
    int potion_cost;    //Will usually be 0. Only cards in the Alchemy set (and maybe the Adventurers set) have potion costs. That I know of.
    std::wstring description;   //The actual text of the card.
    std::wstring extra_information; //Elaboration on the meaning of the card's text. This might originate from the manual, and it might also include details added online.
    std::vector<cardtypes> applicable_types;   //A range containing all of the types that the card matches.

    //take iterators from other containers (like std::array)
    template<typename ContainerItr>
    randomizer_card(const typename ContainerItr b, const typename ContainerItr e)
        : randomizer_card(std::vector<std::wstring>{b, e})
    {};

    randomizer_card(const std::vector<std::wstring>& i);
    randomizer_card(const std::vector<std::wstring>::const_iterator, const std::vector<std::wstring>::const_iterator);
};	//end class randomizer_card
}	//end namespace dominion
}	//end namespace SM (sudden magic)

#endif  // RANDOMIZER_CARD_HPP_INCLUDED