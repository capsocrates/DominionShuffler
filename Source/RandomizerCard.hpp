#ifndef RANDOMIZER_CARD_HPP_INCLUDED
#define RANDOMIZER_CARD_HPP_INCLUDED

/*
  ==============================================================================

    RandomizerCard.hpp
    Created:        14 Sep 2015 11:44:59am
    Author:         Bladerunner
    Description:    A code representation of randomizer cards for generating play decks in the Dominion deck-building game.

  ==============================================================================
*/

#include "Cardsets.hpp"
#include "Cardtypes.hpp"

//stdlib includes
#include <string>
#include <vector>

namespace SM	//(sudden magic)
{
namespace Dominion  //for all of the code related specifically to the deck-building game Dominion.
{

//TODO put cardsets and cardtypes into separate headers

//A class representing a single randomizer card in a deck of randomizer cards.
class RandomizerCard
{
public:
    Cardsets set;   //The set this card belongs to
    std::wstring name;
    //TODO implement costs in terms of boost::optional?
    int gold_cost;  //Might be 0; especially if there is a potion_cost > 0. Some cards may also have special means of being acquired, like the Urchin and Mercenary. These cards will have a cost of 0.
    int potion_cost;    //Will usually be 0. Only cards in the Alchemy set (and maybe the Adventurers set) have potion costs. That I know of.
    std::wstring description;   //The actual text of the card.
    std::wstring extra_information; //Elaboration on the meaning of the card's text. This might originate from the manual, and it might also include details added online.
    std::vector<Cardtypes> applicable_types;   //A range containing all of the types that the card matches.

    //take iterators from other containers (like std::array)
    template<typename ContainerItr>
    RandomizerCard(const typename ContainerItr b, const typename ContainerItr e)
        : RandomizerCard(std::vector<std::wstring>{b, e})
    {};

    RandomizerCard(const std::vector<std::wstring>& i);
    RandomizerCard(const std::vector<std::wstring>::const_iterator, const std::vector<std::wstring>::const_iterator);
};	//end class RandomizerCard
}	//end namespace Dominion
}	//end namespace SM (sudden magic)

#endif  // RANDOMIZER_CARD_HPP_INCLUDED