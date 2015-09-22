/*
  ==============================================================================

    CardsetToggleListener.cpp
    Created: 22 Sep 2015 3:43:02pm
    Author:  caps

  ==============================================================================
*/

#include "CardsetToggleListener.hpp"

#include "cardsets.hpp"
#include "CardShuffler.hpp"

#include <cassert>

namespace SM
{
namespace Dominion
{
CardsetToggleListener::CardsetToggleListener(Cardsets set, CardShuffler& shuf)
    : set(set)
    , shuf(shuf)
{
}

auto CardsetToggleListener::valueChanged(juce::Value& val) -> void
{
    assert(val.getValue().isBool());
    if (val.getValue().operator bool())
        shuf.enableCardset(set);
    else
        shuf.disableCardset(set);
}

}   //end namespace Dominion
}   //end namepsace SM