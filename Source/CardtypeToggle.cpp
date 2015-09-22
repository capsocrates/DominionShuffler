/*
  ==============================================================================

    CardtypeToggle.cpp
    Created: 22 Sep 2015 10:30:12am
    Author:  caps

  ==============================================================================
*/

#include "CardtypeToggle.hpp"

#include "CardShuffler.hpp"

#include "../JuceLibraryCode/JuceHeader.h"

namespace SM
{
namespace Dominion
{
//==============================================================================
CardtypeToggle::CardtypeToggle(const Cardtypes type, CardShuffler& shuf)
    : BooleanPropertyComponent((str_from_cardtype(type) + L"Toggle").c_str(), (str_from_cardtype(type) + L" enabled").c_str(), (str_from_cardtype(type) + L" disabled").c_str())
    , type(type)
    , shuf(shuf)
{}
//==============================================================================
auto CardtypeToggle::setState(bool newState) -> void
{
    if (newState)
        shuf.enableCardtype(type);
    else
        shuf.disableCardtype(type);

    juce::BooleanPropertyComponent::setState(newState);
}
//==============================================================================
}   //end namespace Dominion
}   //end namespace SM