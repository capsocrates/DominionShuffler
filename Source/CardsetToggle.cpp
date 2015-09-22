/*
  ==============================================================================

    CardsetToggle.cpp
    Created: 22 Sep 2015 10:30:12am
    Author:  caps

  ==============================================================================
*/

#include "CardsetToggle.hpp"

#include "CardShuffler.hpp"

#include "../JuceLibraryCode/JuceHeader.h"

namespace SM
{
namespace Dominion
{
//==============================================================================
CardsetToggle::CardsetToggle(const Cardsets set, CardShuffler& shuf)
    : BooleanPropertyComponent((str_from_cardset(set) + L"Toggle").c_str(), (str_from_cardset(set) + L" enabled").c_str(), (str_from_cardset(set) + L" disabled").c_str())
    , set(set)
    , shuf(shuf)
{}
//==============================================================================
auto CardsetToggle::setState(bool newState) -> void
{
    if (newState)
        shuf.enableCardset(set);
    else
        shuf.disableCardset(set);

    juce::BooleanPropertyComponent::setState(newState);
}
//==============================================================================
}   //end namespace Dominion
}   //end namespace SM