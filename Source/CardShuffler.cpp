/*
  ==============================================================================

    card_shuffler.cpp
    Created: 21 Sep 2015 1:51:09pm
    Author:  caps

  ==============================================================================
*/

#include "CardShuffler.hpp"

namespace SM
{
namespace Dominion
{
CardShuffler::CardShuffler()
    : generator(engine())
{
}

}   //end namespace Dominion
}   //end namespace SM